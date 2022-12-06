#include "gb_utils.h"

#include <stdio.h>

bool read_graph(char* graph_name, struct Graph* G) {
  // initialize graph struct
  // char info[50] = "../benchmarks/";
  // strcat(info, graph_name);
  // strcat(info, "/info.txt");
  char info[] = "../benchmarks/qsort/info.txt";
  FILE *fp = fopen(info, "r");

  int num_nodes, num_edges, num_nd;
  fscanf(fp, "%d %d %d", &num_nodes, &num_edges, &num_nd);
  fclose(fp);
  
  G->num_nodes = num_nodes;
  G->num_edges = num_edges;
  G->num_nd = num_nd;

  // initialize nd_nodes array  
  // char nd_nodes[50] = "../benchmarks/";
  // strcat(nd_nodes, graph_name);
  // strcat(nd_nodes, "/nd_nodes.txt");
  char nd_nodes[50] = "../cpp2/qsort-nd/nd_nodes/";
  strcat(nd_nodes, graph_name);
  fp = fopen(nd_nodes, "r");

  G->nd_nodes = (GrB_Index*) malloc(sizeof(GrB_Index) * num_nd);
  int value;
  size_t counter = 0;
  while (!feof(fp)) {
    fscanf(fp, "%d\n", &value);
    G->nd_nodes[counter++] = value;
  }
  fclose(fp);

  // create adjacency matrix
  // char edges[50] = "../benchmarks/";
  // strcat(edges, graph_name);
  // strcat(edges, "/edges.el");
  char edges[] = "../benchmarks/qsort/edges.el";
  fp = fopen(edges, "r");

  GrB_Matrix_new(&G->adjacency_matrix, GrB_BOOL, G->num_nodes, G->num_nodes);
  while (!feof(fp)) {
    int src, dst;
    fscanf(fp, "%d %d\n", &src, &dst);
    GrB_Matrix_setElement_BOOL(G->adjacency_matrix, true, src, dst);
  }
  fclose(fp);

  // create graph
  int result = LAGraph_New(&G->la_graph, &G->adjacency_matrix, LAGraph_ADJACENCY_DIRECTED, G->error);
  return result == GrB_SUCCESS;
}

void bfs(struct Graph* G, bool* nondeterministic) {
  for (size_t i = 0; i < G->num_nd; i++) {
    GrB_Index src = G->nd_nodes[i];

    GrB_Vector vector;
    LAGr_BreadthFirstSearch(NULL, &vector, G->la_graph, src, G->error);

    GrB_Index max_size = G->num_nodes;
    GrB_Index indices[max_size];
    bool values[max_size];
    GrB_Vector_extractTuples_BOOL(indices, values, &max_size, vector);

    for (size_t j = 0; j < max_size; ++j) {
      nondeterministic[indices[j]] = true;
    }
  }
}

void bfs_mod(struct Graph* G, bool* nondeterministic) {
  GrB_Vector vector;  
  int result = mybfs(&vector, G->la_graph, G->nd_nodes, G->num_nd, G->error);
  if (result != GrB_SUCCESS) {
    printf("%s", G->error);
    return;
  }

  GrB_Index max_size = G->num_nodes;
  GrB_Index indices[max_size];
  bool values[max_size];
  GrB_Vector_extractTuples_BOOL(indices, values, &max_size, vector);

  for (size_t j = 0; j < max_size; ++j) {
    nondeterministic[indices[j]] = true;
  }
}
