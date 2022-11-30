#include "propagate_flags.h"

#include <deque> 
#include <vector>

namespace {
  std::deque<int> get_nondeterministic_nodes(const IFTGraph& G) {
    std::deque<int> v;
    for (size_t i = 0; i < G.nodes.size(); ++i) {
      if (G.nodes[i].nondeterministic) v.push_back(i);
    }
    return v;
  }

  void update_flag(IFTGraph& G, int nidx) {
    std::vector<int> children = G.child_map[nidx];
    for (int cidx : children) {
      IFTGraph::IFTNode& child = G.nodes[cidx];
      if (!child.nondeterministic) {
        child.nondeterministic = true;
        update_flag(G, cidx);
      }
    }
  }
}
void RecursivePropagate::propagate_flags(IFTGraph& G) {
  std::deque<int> prop_nd_nodes = get_nondeterministic_nodes(G);
  for (int nidx : prop_nd_nodes) update_flag(G, nidx);
}