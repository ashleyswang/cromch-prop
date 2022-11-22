#include "gb_utils.h"

#include <stdio.h>

bool read_graph(char* graph_name, struct Graph* G) {
  char fname[35] = "../benchmarks/";
  strcat(fname, graph_name);
  strcat(fname, "/edges.el");

  FILE *fp = fopen(fname, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error opening file %s\n", fname);
    return false;
  }
  fclose(fp);
  
  // create adjacency matrix
  GrB_Matrix_new(&G->adjacency_matrix, GrB_BOOL, G->num_nodes, G->num_nodes);
  while (!feof(fp)) {
    int src, dst;
    fscanf(fp, "%d %d\n", &src, &dst);
    GrB_Matrix_setElement_BOOL(G->adjacency_matrix, true, src, dst);
  }

  // create graph
  int result = LAGraph_New(&G->la_graph, &G->adjacency_matrix, LAGraph_ADJACENCY_DIRECTED, G->error);
  return result == GrB_SUCCESS;
}