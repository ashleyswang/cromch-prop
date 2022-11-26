#ifndef GB_UTILS_H
#define GB_UTILS_H

#include "GraphBLAS.h"
#include "LAGraph.h"
#include "LAGraphX.h"

struct Graph {
  size_t num_nodes;
  size_t num_edges;
  size_t num_nd;
  size_t* nd_nodes;

  GrB_Matrix adjacency_matrix;
  LAGraph_Graph la_graph;
  char* error;
};

/* Outputs initialized LAGraph*/
bool read_graph(char* graph_name, struct Graph* graph);

/* Single threaded naive approach */
void bfs(struct Graph* graph, bool* nondeterministic);
/* Multi threaded naive approach */
void bfs_multi(struct Graph* graph, bool* nondeterministic);

/* Multi threaded naive approach */
void bfs_mod(struct Graph* graph, bool* nondeterministic);

int mybfs(
    GrB_Vector *parent,
    const LAGraph_Graph G,
    GrB_Index* src,
    size_t num_nd,
    char *msg
);

#endif  // GB_UTILS_H