#ifndef IFT_GRAPH_H
#define IFT_GRAPH_H

#include <string>
#include <vector>

struct IFTGraph {

  struct IFTNode {
    uint32_t node_idx;
    uint32_t commit_id;
    std::string node_str;
    bool nondeterministic;

    std::string toString() {
      return "#" + std::to_string(commit_id) + " " + node_str;
    };
  };

  struct IFTEdge {
    uint32_t src;
    uint32_t dst;
  };

  std::vector<IFTNode> nodes;
  std::vector<IFTEdge> edges;
  std::vector<std::vector<int>> child_map;

  std::vector<int> get_children(int node_idx);
};

#endif  // IFT_GRAPH_H