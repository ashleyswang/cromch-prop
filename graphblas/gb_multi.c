#include "gb_utils.h"

#include <stdio.h>
#include <pthread.h>
#include <math.h>

/* helper function & struct */

#define NUM_THREADS 10

struct bfs_multi_args {
  struct Graph* G;
  bool* nondeterministic;
  size_t start;
  size_t end;
};

void* bfs_single(void* vargs) {
  struct bfs_multi_args* args = (struct bfs_multi_args*) vargs;
  struct Graph* G = args->G;

  char* error;
  LAGraph_Graph la_graph;
  LAGraph_New(&la_graph, &G->adjacency_matrix, LAGraph_ADJACENCY_DIRECTED, error);

  for (size_t i = args->start; i < args->end; i++) {
    GrB_Index src = G->nd_nodes[i];

    GrB_Vector vector;
    LAGr_BreadthFirstSearch(NULL, &vector, la_graph, src, error);

    GrB_Index max_size = G->num_nodes;
    GrB_Index indices[max_size];
    bool values[max_size];
    GrB_Vector_extractTuples_BOOL(indices, values, &max_size, vector);

    for (size_t j = 0; j < max_size; ++j) {
      // args->nondeterministic[indices[j]] = true;
    }
  }
}

void bfs_multi(struct Graph* graph, bool* nondeterministic) {
  int increment = ceil((float)(graph->num_nd) / NUM_THREADS);
  size_t start = 0, end = increment;
  
  pthread_t threads[NUM_THREADS];
  for (size_t i = 0; i < NUM_THREADS; i++) {
    if (i == NUM_THREADS - 1) end = graph->num_nd;
    struct bfs_multi_args args;
    args.G = graph;
    args.nondeterministic = nondeterministic;
    args.start = start;
    args.end = end;
    pthread_create(&threads[i], NULL, bfs_single, (void*)&args);
    start += increment;
    end += increment;
  }

  for (size_t i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);
}

#undef NUM_THREADS