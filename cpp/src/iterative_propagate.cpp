#include "propagate_flags.h"

#include <deque> 
#include <vector>

namespace {
  std::deque<int> get_nondeterministic_nodes(const IFTGraph& G) {
    std::deque<int> v;
    for (int i = 0; i < G.nodes.size(); ++i) {
      if (G.nodes[i].nondeterministic) v.push_back(i);
    }
    return v;
  }
}
void IterativePropagate::propagate_flags(IFTGraph& G) {
  std::deque<int> prop_nd_nodes = get_nondeterministic_nodes(G);
  while(!prop_nd_nodes.empty()) {
    int nidx = prop_nd_nodes.front();
    prop_nd_nodes.pop_front();
  
    std::vector<int> children = G.child_map[nidx];
    for (int cidx : children) {
      IFTGraph::IFTNode& child = G.nodes[cidx];
      if (!child.nondeterministic) {
        child.nondeterministic = true;
        prop_nd_nodes.push_back(cidx);
      }
    }
  }
}