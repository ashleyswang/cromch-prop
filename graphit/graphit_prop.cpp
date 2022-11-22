#include <iostream> 
#include <vector>
#include <algorithm>
#include "intrinsics.h"
#ifdef GEN_PYBIND_WRAPPERS
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
namespace py = pybind11;
#endif
Graph edges;
bool  * __restrict nondeterministic;
template <typename TO_FUNC , typename APPLY_FUNC> VertexSubset<NodeID>* edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier2(Graph & g , VertexSubset<NodeID>* from_vertexset, TO_FUNC to_func, APPLY_FUNC apply_func) 
{ 
    int64_t numVertices = g.num_nodes(), numEdges = g.num_edges();
    from_vertexset->toSparse();
    long m = from_vertexset->size();
    // used to generate nonzero indices to get degrees
    uintT *degrees = newA(uintT, m);
    // We probably need this when we get something that doesn't have a dense set, not sure
    // We can also write our own, the eixsting one doesn't quite work for bitvectors
    //from_vertexset->toSparse();
    {
        ligra::parallel_for_lambda((long)0, (long)m, [&] (long i) {
            NodeID v = from_vertexset->dense_vertex_set_[i];
            degrees[i] = g.out_degree(v);
         });
    }
    uintT outDegrees = sequence::plusReduce(degrees, m);
    VertexSubset<NodeID> *next_frontier = new VertexSubset<NodeID>(g.num_nodes(), 0);
    if (numVertices != from_vertexset->getVerticesRange()) {
        cout << "edgeMap: Sizes Don't match" << endl;
        abort();
    }
    if (outDegrees == 0) return next_frontier;
    uintT *offsets = degrees;
    long outEdgeCount = sequence::plusScan(offsets, degrees, m);
    uintE *outEdges = newA(uintE, outEdgeCount);
  for (long i=0; i < m; i++) {
    NodeID s = from_vertexset->dense_vertex_set_[i];
    int j = 0;
    uintT offset = offsets[i];
    for(NodeID d : g.out_neigh(s)){
      if (to_func(d)) { 
        if( apply_func ( s , d  ) ) { 
          outEdges[offset + j] = d; 
        } else { outEdges[offset + j] = UINT_E_MAX; }
      } //end of to func
       else { outEdges[offset + j] = UINT_E_MAX;  }
      j++;
    } //end of for loop on neighbors
  }
  uintE *nextIndices = newA(uintE, outEdgeCount);
  long nextM = sequence::filter(outEdges, nextIndices, outEdgeCount, nonMaxF());
  free(outEdges);
  free(degrees);
  next_frontier->num_vertices_ = nextM;
  next_frontier->dense_vertex_set_ = nextIndices;
  return next_frontier;
} //end of edgeset apply function 
extern string edge_fname (string graph_name); 
extern void read_nd_nodes (string graph_name); 
struct nondeterministic_generated_vector_op_apply_func_0
{
void operator() (NodeID v) 
  {
    nondeterministic[v] = (bool) 0;
  };
};
extern string edge_fname (string graph_name); 
extern void read_nd_nodes (string graph_name); 
struct ndFilter
{
bool operator() (NodeID v) 
  {
    bool output ;
    output = nondeterministic[v];
    return output;
  };
};
struct updateFlag
{
bool operator() (NodeID src, NodeID dst) 
  {
    bool output1 ;
    nondeterministic[dst] = (bool) 1;
    output1 = (bool) 1;
    return output1;
  };
};
struct toFilter
{
bool operator() (NodeID v) 
  {
    bool output ;
    output =  !(nondeterministic[v]);
    return output;
  };
};
struct printNondeterminism
{
void operator() (NodeID v) 
  {
    if (nondeterministic[v])
     { 
      std::cout << v<< std::endl;
     } 
  };
};
int main(int argc, char * argv[])
{
  edges = builtin_loadEdgesFromFile ( edge_fname(argv_safe((1) , argv, argc)) ) ;
  nondeterministic = new bool [ builtin_getVertices(edges) ];
  ligra::parallel_for_lambda((int)0, (int)builtin_getVertices(edges) , [&] (int vertexsetapply_iter) {
    nondeterministic_generated_vector_op_apply_func_0()(vertexsetapply_iter);
  });;
  int iter = atoi(argv_safe((2) , argv, argc)) ;
  for ( int i = (0) ; i < iter; i++ )
  {
    startTimer() ;
    read_nd_nodes(argv_safe((1) , argv, argc)) ;
    VertexSubset<int> *  frontier = builtin_const_vertexset_filter <ndFilter>(ndFilter(), builtin_getVertices(edges) );
    while ( (builtin_getVertexSetSize(frontier) ) != ((0) ))
    {
      VertexSubset<int> *  output ;
      output = edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier2(edges, frontier, toFilter(), updateFlag()); 
      deleteObject(frontier) ;
      frontier = output;
    }
    deleteObject(frontier) ;
    float time = (stopTimer()  * (1000) );
    std::cout << time<< std::endl;
  }
  ligra::parallel_for_lambda((int)0, (int)builtin_getVertices(edges) , [&] (int vertexsetapply_iter) {
    printNondeterminism()(vertexsetapply_iter);
  });;
};
#ifdef GEN_PYBIND_WRAPPERS
PYBIND11_MODULE(, m) {
}
#endif

