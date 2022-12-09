#include <cstring>
#include <fstream>
#include <string>

std::string edge_fname(std::string graph_name) {
  std::string fname = "../benchmarks/" + graph_name + "/edges.el";
  return fname;
}

extern bool * nondeterministic;

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