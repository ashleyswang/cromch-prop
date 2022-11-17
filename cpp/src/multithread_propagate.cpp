#include "propagate_flags.h"

#include <deque>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <vector>

#define NUM_THREADS 10

namespace {
  struct Args {
    Args(IFTGraph& G, std::deque<int>& nondeterministic_nodes) : 
      G(G), nondeterministic_nodes(nondeterministic_nodes) {}
    
    IFTGraph& G;
    std::deque<int>& nondeterministic_nodes;
    pthread_mutex_t mutex;
    int num_threads = 0;
  };

  std::vector<int> get_nondeterministic_nodes(const IFTGraph& G) {
    std::vector<int> v;
    for (int i = 0; i < G.nodes.size(); ++i) {
      if (G.nodes[i].nondeterministic) v.push_back(i);
    }
    return v;
  }

  void* update_flag(void *param) {
    Args* args = static_cast<Args*> (param);

    while (!args->nondeterministic_nodes.empty()) {
      pthread_mutex_lock(&args->mutex);
      int nidx = args->nondeterministic_nodes.front();
      args->nondeterministic_nodes.pop_front();
      pthread_mutex_lock(&args->mutex);

      auto children = args->G.child_map[nidx];
      for (int cidx : children) {
        IFTGraph::IFTNode& child = args->G.nodes[cidx];
        if (!child.nondeterministic) {
          child.nondeterministic = true;
          pthread_mutex_lock(&args->mutex);
          args->nondeterministic_nodes.push_back(cidx);
          pthread_mutex_unlock(&args->mutex);
        }
      }
    }
  }

  void update_flag2(IFTGraph& G, int nidx) {
    // printf("%d ", nidx);
    std::vector<std::thread> threads; 
    auto children = G.child_map[nidx];
    for (int cidx : children) {
      IFTGraph::IFTNode& child = G.nodes[cidx];
      if (!child.nondeterministic) {
        child.nondeterministic = true;
        threads.emplace_back(std::thread(update_flag2, std::ref(G), cidx));
      }
    }

    for (auto& t : threads) t.join();
  }

  void update_flag3(IFTGraph& G, std::vector<int> nd_nodes, int init) {
    std::vector<std::thread> threads; 
    if (init) {
      for (int nidx : nd_nodes) {
        auto children = G.child_map[nidx];
        threads.emplace_back(std::thread(update_flag3, std::ref(G), children, 0));
      }
      for (auto& t : threads) t.join();
    } else {
      for (int nidx : nd_nodes) {
        auto& node = G.nodes[nidx];
        if (!node.nondeterministic) {
          node.nondeterministic = true;
          auto children = G.child_map[nidx];
          threads.emplace_back(std::thread(update_flag3, std::ref(G), children, 0));
        }
      }
      for (auto& t : threads) t.join();
    }
  }
}

// void MultithreadPropagate::propagate_flags(IFTGraph& G) {
//   std::deque<int> nd_nodes = get_nondeterministic_nodes(G);
//   Args args = {G, nd_nodes};

//   pthread_t threads[NUM_THREADS];
//   for (int i = 0; i < NUM_THREADS; i++) {
//     pthread_create(&threads[i], 0, &update_flag, (void*)&args);
//   }

//   for (auto thread : threads) pthread_join(thread, 0);
// }


void MultithreadPropagate::propagate_flags(IFTGraph& G) {
  std::vector<int> nd_nodes = get_nondeterministic_nodes(G);
  
  update_flag3(G, nd_nodes, 1);
}
