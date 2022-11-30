#include <chrono>
#include <fstream>
#include <iostream> 
#include <sstream> 
#include <string>

#include "ift.h"
#include "propagate_flags.h"

IFTGraph read_graph(std::string graph) {
	IFTGraph G;
	G.graph = graph;

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
	// std::cout << graph << " num nodes: " << G.nodes.size() << std::endl;

	/* Parse edges */
	G.child_map.resize(G.nodes.size());
	ifs.open("../benchmarks/" + graph + "/edges.el");
	while (!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) break;

		IFTGraph::IFTEdge edge;
		std::stringstream s(line);
		getline(s, word, ' ');
		edge.src = stoi(word);
		getline(s, word, ' ');
		edge.dst = stoi(word);
		G.edges.push_back(edge);

		G.child_map[edge.src].push_back(edge.dst);
	}
	ifs.close();
	// std::cout << graph << " num edges: " << G.edges.size() << std::endl;
	return G;
}

void output_graph(IFTGraph& G, std::string graph, std::string method) {
	std::ofstream ofs;
	ofs.open("../benchmarks/" + graph + "/graphs/" + graph + "_" + method + ".dot");

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
	if (propagate_method == "recur") propagate = new RecursivePropagate();
	if (propagate_method == "multi") propagate = new MultithreadPropagate();
	if (propagate_method == "multir") propagate = new MultiRecurPropagate();
	// if (propagate_method == "gt") propagate = new GraphItPropagate();

	int num_iter = 0;
	bool make_graph = false; 
	bool output = false;
	for (int i = 3; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--repeat") num_iter = atoi(argv[i + 1]);
		if (arg == "--graph") make_graph = true;
		if (arg == "--output") output = true;
	}

	// Create graph object
	IFTGraph graph = read_graph(argv[1]);

	// Propagation
	for (int i = 0; i < num_iter; ++i) {
		IFTGraph G = graph;
		auto start = std::chrono::high_resolution_clock::now();
		propagate->propagate_flags(G);
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = stop - start;
		// std::cout << "Propagation time: " << ms_double.count() << " ms" << std::endl;
		std::cout << ms_double.count() << std::endl;
	}
 
	// Output to .dot file
	if (make_graph || output) propagate->propagate_flags(graph);
	if (make_graph) output_graph(graph, argv[1], argv[2]);
	if (output) {
		for (auto node : graph.nodes) {
			if (node.nondeterministic) std::cout << node.node_idx << std::endl;
		}
	}
	
	delete propagate;
  return 0;
}