#include "GraphBLAS.h"
#include "LAGraph.h"
#include "LAGraphX.h"

#include "gb_utils.h"

//   // do BFS and output all visited nodes
//   GrB_Vector vector;
//   // gotta do this for all the non deterministic nodes, idk seems kinda like a lot of work but i suppose you could multithread each bfs call, but then is it really worth it to use graphblas? idk sober ashley
//   // you figure it out <3 -high ashley
//   // wait but also to check for the actual node, you can just check the index in the output vector
//   // i think it'll have a -1 or null if it is never reached
//   LAGr_BreadthFirstSearch(nullptr, &vector, graph, index, msg);

//   // then you get the indices and then you iterate through the node list
//   // get the node pointer from the index and then make it non deterministic if it is not already nondeterministic
// }

// #undef NUM_NODES

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "USAGE: ./main <benchmark_name> <num_nodes>");
    return 1;
  }

  struct Graph G;
  G.num_nodes = atoi(argv[2]);
  read_graph(argv[1], &G);
}