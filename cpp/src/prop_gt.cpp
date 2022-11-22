#include "propagate_flags.h"
#include "gt_module.h"

void GraphItPropagate::setup(IFTGraph& G) {
  gt_setup() ("cromch-prop/benchmarks/" + G.graph + "/edges.el");
  for (auto& node : G.nodes) {
    if (node.nondeterministic) nondeterministic[node.node_idx] = true;
  }
}

void GraphItPropagate::propagate_flags(IFTGraph& G) {
  gt_prop_flags() ();
}