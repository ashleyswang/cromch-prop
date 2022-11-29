#include "GraphBLAS.h"
#include "LAGraph.h"
#include "LAGraphX.h"

#include <time.h>

#include "gb_utils.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "USAGE: ./main <benchmark_name> <num_iterations> <output_file>");
    return 1;
  }
  int num_iterations = atoi(argv[2]);
  FILE* fp = (argc == 4) ? fopen(argv[3], "w") : stdout;

  GrB_init(GrB_NONBLOCKING);

  struct Graph G;
  read_graph(argv[1], &G);

  bool nondeterministic[G.num_nodes];
  for (int i = 0; i < num_iterations; i++) {  
    for (size_t i = 0; i < G.num_nodes; i++) {
      nondeterministic[i] = false;
    }
    clock_t start = clock();
    // bfs(&G, nondeterministic);
    bfs_mod(&G, nondeterministic);
    clock_t end = clock();
    double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time * 1000);
  }
  
  GrB_finalize();
  free(G.nd_nodes);

  // for (size_t i = 0; i < G.num_nodes; i++) {
  //   if (nondeterministic[i]) fprintf(fp, "%d\n", i);
  // }
  if (argc == 4) fclose(fp);
  
  return 0;
}