#include "propagate_flags.h"

#include <cmath>
#include <deque>

#include <thread>
#include <mutex>
#include <vector>

#define NUM_THREADS 10

namespace {
  std::vector<int> get_nondeterministic_nodes(const IFTGraph& G) {
    std::vector<int> v;
    for (size_t i = 0; i < G.nodes.size(); ++i) {
      if (G.nodes[i].nondeterministic) v.push_back(i);
    }
    return v;
  }

  void update_flag(IFTGraph& G, std::deque<int> nondeterministic_nodes) {
    while (!nondeterministic_nodes.empty()) {
      int nidx = nondeterministic_nodes.front();
      nondeterministic_nodes.pop_front();

      auto children = G.child_map[nidx];
      for (int cidx : children) {
        IFTGraph::IFTNode& child = G.nodes[cidx];
        if (!child.nondeterministic) {
          child.nondeterministic = true;
          nondeterministic_nodes.push_back(cidx);
        }
      }
    }
  }
}


void MultithreadPropagate::propagate_flags(IFTGraph& G) {
  std::vector<int> nd_nodes = get_nondeterministic_nodes(G);

  auto increment = ceil(float(nd_nodes.size()) / NUM_THREADS);
  auto start = nd_nodes.begin(), end = nd_nodes.begin() + increment - 1;
  std::vector<std::thread> threads(NUM_THREADS);
  for (size_t i = 0; i < NUM_THREADS; i++) {
    if (i == NUM_THREADS - 1) end = nd_nodes.end();
    std::deque<int> prop_nodes(start, end);
    threads.emplace_back(std::thread(update_flag, std::ref(G), prop_nodes));
    start += increment;
    end += increment;
  }

  for (auto& t : threads) t.join();
}
