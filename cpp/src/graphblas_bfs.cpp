#include "propagate_flags.h"

// #include "GraphBLAS.h"
// #include "LAGraph.h"
// #include "LAGraphX.h"

void GraphBlasBFS::propagate_flags(IFTGraph& G) {
//   // make adjacency matrix
//   GrB_Matrix adj_matrix;
//   GrB_Matrix_new(&adj_matrix, GrB_BOOL, G.nodes.size(), G.nodes.size());
//   for (auto& edge : G.edges) {
//     GrB_Matrix_setElement_BOOL(adj_matrix, true, edge.src, edge.dst);
//   }

//   // make graph
//   char* error;
//   LAGraph_Graph la_graph;
//   LAGraph_New(&la_graph, &adj_matrix, LAGraph_ADJACENCY_DIRECTED, error);
}
  


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