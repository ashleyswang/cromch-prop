#include "propagate_flags.h"
#include "gt_module.h"

#include <fstream>
#include <string>

void read_nd_nodes(std::string graph_name) {
  std::ifstream ifs;
	ifs.open("../benchmarks/" + graph_name + "/nd_nodes.txt");

  std::string line;
	while(!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) break;

		int idx = stoi(line);
    nondeterministic[idx] = true;
	}
	ifs.close();
}

void GraphItPropagate::propagate_flags(IFTGraph& G) {
  gt_prop_flags() (G.graph);
}