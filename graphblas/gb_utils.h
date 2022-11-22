#ifndef GB_UTILS_H
#define GB_UTILS_H

#include "GraphBLAS.h"
#include "LAGraph.h"
#include "LAGraphX.h"

struct Graph {
  size_t num_nodes;
  size_t[] nd_nodes;
  GrB_Matrix adjacency_matrix;
  LAGraph_Graph la_graph;
  char* error;
};

/* Outputs initialized LAGraph*/
bool read_graph(char* graph_name, struct Graph* graph);

#endif  // GB_UTILS_H