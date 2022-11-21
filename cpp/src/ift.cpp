#include "ift.h"

namespace {
  int binary_search_index(const std::vector<IFTGraph::IFTEdge>& v, 
                          int target, size_t start_idx, size_t end_idx) {
    // exhausted binary search
    if (start_idx == end_idx) 
      return target == v[end_idx].src ? end_idx : -1;

    int mid_idx = (start_idx + end_idx) / 2;
    int value = v[mid_idx].src;
    if (target == value) return mid_idx;
    if (target < value) return binary_search_index(v, target, start_idx, mid_idx);
    if (target > value) return binary_search_index(v, target, mid_idx + 1, end_idx);
    return -1;
  }

  int binary_search_index(const std::vector<IFTGraph::IFTEdge>& v, int target) {
    return binary_search_index(v, target, 0, v.size() - 1);
  }
}

// space vs. memory? we could make this a lot faster by using more memory
std::vector<int> IFTGraph::get_children(int node_idx) {
  std::vector<int> v;
  int test_idx = binary_search_index(edges, node_idx);
  if (test_idx < 0) return v;

  size_t curr_idx = test_idx;
  while (edges[curr_idx].src == node_idx) {
    v.push_back(edges[curr_idx].dst);
    curr_idx--;
  }
  curr_idx = test_idx + 1;
  while (edges[curr_idx].src == node_idx) {
    v.push_back(edges[curr_idx].dst);
    curr_idx++;
  }
  return v;
}