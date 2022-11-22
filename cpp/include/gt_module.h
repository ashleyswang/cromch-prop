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
template <typename TO_FUNC , typename APPLY_FUNC> VertexSubset<NodeID>* edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier1(Graph & g , VertexSubset<NodeID>* from_vertexset, TO_FUNC to_func, APPLY_FUNC apply_func) 
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
    bool output0 ;
    nondeterministic[dst] = (bool) 1;
    output0 = (bool) 1;
    return output0;
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
struct gt_setup
{
void operator() (string graph) 
  {
    edges = builtin_loadEdgesFromFile ( graph) ;
    (bool) 1;
    nondeterministic = new bool [ builtin_getVertices(edges) ];
  };
};
#ifdef GEN_PYBIND_WRAPPERS
//PyBind Wrappers for functiongt_setup
void gt_setup__wrapper (string graph) { 
  gt_setup()(graph);
}
#endif
struct gt_prop_flags
{
void operator() () 
  {
    VertexSubset<int> *  frontier = builtin_const_vertexset_filter <ndFilter>(ndFilter(), builtin_getVertices(edges) );
    while ( (builtin_getVertexSetSize(frontier) ) != ((0) ))
    {
      VertexSubset<int> *  output ;
      output = edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier1(edges, frontier, toFilter(), updateFlag()); 
      deleteObject(frontier) ;
      frontier = output;
    }
    deleteObject(frontier) ;
  };
};
#ifdef GEN_PYBIND_WRAPPERS
//PyBind Wrappers for functiongt_prop_flags
void gt_prop_flags__wrapper (void) { 
  gt_prop_flags()();
}
#endif
#ifdef GEN_PYBIND_WRAPPERS
PYBIND11_MODULE(, m) {
m.def("gt_setup", &gt_setup__wrapper, "");
m.def("gt_prop_flags", &gt_prop_flags__wrapper, "");
}
#endif

