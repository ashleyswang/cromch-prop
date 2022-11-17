#include <chrono>
#include <fstream>
#include <iostream> 
#include <sstream> 
#include <string>

#include "ift.h"
#include "propagate_flags.h"

IFTGraph read_graph(std::string graph) {
	IFTGraph G;

	/* Parse nodes */
	std::ifstream ifs;
	ifs.open("../benchmarks/" + graph + "/nodes.txt");
	
	std::string line, word;
	while(!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) break;

		IFTGraph::IFTNode node;
		std::stringstream s(line);
		for (int i = 0; i < 4; ++i) {
			getline(s, word, ',');

			switch (i) {
				case 0:
					node.node_idx = stoi(word);
					break;
				case 1: 
					node.commit_id = stoi(word);
					break;
				case 2: 
					node.node_str = word;
					break;
				case 3:
					node.nondeterministic = bool(stoi(word));
			}
		}
		G.nodes.push_back(node);
	}
	ifs.close();
	std::cout << graph << " num nodes: " << G.nodes.size() << std::endl;

	/* Parse edges */
	G.child_map.resize(G.nodes.size());
	ifs.open("../benchmarks/" + graph + "/edges.txt");
	while (!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) break;

		IFTGraph::IFTEdge edge;
		std::stringstream s(line);
		getline(s, word, ',');
		edge.src = stoi(word);
		getline(s, word, ',');
		edge.dst = stoi(word);
		G.edges.push_back(edge);

		G.child_map[edge.src].push_back(edge.dst);
	}
	ifs.close();
	std::cout << graph << " num edges: " << G.edges.size() << std::endl;
	return G;
}

void output_graph(IFTGraph& G, std::string graph, std::string method) {
	std::ofstream ofs;
	ofs.open("../benchmarks/" + graph + "/" + graph + "_" + method + ".dot");

	ofs << "digraph {\n";

	for (auto node : G.nodes) {
		std::string color = node.nondeterministic ? "#ef9148" : "#1ABA8B";
		ofs << "\"" << node.toString() << "\" [ color = \"" << color 
				<< "\", shape = \"box\", label = \"" << node.toString() << "\" ];\n";
	}

	for (auto edge : G.edges) {
		auto src = G.nodes[edge.src];
		auto dst = G.nodes[edge.dst];
		ofs << "\"" << src.toString() << "\" -> \"" << dst.toString() << "\" ;\n";
	}

	ofs << "}\n";
	ofs.close();
}

int main (int argc, char *argv[]) {
	PropagateFlags* propagate = nullptr;

	if (argc < 3) {
		std::cerr << "USAGE: ./propagate_flags <graph_dir> <propagate_method>" << std::endl;
	}

	// Choose propagate method
	std::string propagate_method = argv[2];
	if (propagate_method == "iter") propagate = new IterativePropagate();
	if (propagate_method == "multi") propagate = new MultithreadPropagate();

	// Create graph object
	IFTGraph G = read_graph(argv[1]);

	// Propagation
	auto start = std::chrono::high_resolution_clock::now();
	propagate->propagate_flags(G);
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = stop - start;
	std::cout << "Propagation time: " << ms_double.count() << " ms" << std::endl;
 
	// Output to .dot file
	output_graph(G, argv[1], argv[2]);
	delete propagate;
  return 0;
}