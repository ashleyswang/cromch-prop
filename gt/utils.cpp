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

// IFTGraph read_graph(std::string graph) {
// 	IFTGraph G;

// 	/* Parse nodes */
// 	std::ifstream ifs;
// 	ifs.open("../benchmarks/" + graph + "/nodes.txt");
	
// 	std::string line, word;
// 	while(!ifs.eof()) {
// 		getline(ifs, line);
// 		if (line.empty()) break;

// 		IFTGraph::IFTNode node;
// 		std::stringstream s(line);
// 		for (int i = 0; i < 4; ++i) {
// 			getline(s, word, ',');

// 			switch (i) {
// 				case 0:
// 					node.node_idx = stoi(word);
// 					break;
// 				case 1: 
// 					node.commit_id = stoi(word);
// 					break;
// 				case 2: 
// 					node.node_str = word;
// 					break;
// 				case 3:
// 					node.nondeterministic = bool(stoi(word));
// 			}
// 		}
// 		G.nodes.push_back(node);
// 	}
// 	ifs.close();
// 	// std::cout << graph << " num nodes: " << G.nodes.size() << std::endl;

// 	/* Parse edges */
// 	G.child_map.resize(G.nodes.size());
// 	ifs.open("../benchmarks/" + graph + "/edges.txt");
// 	while (!ifs.eof()) {
// 		getline(ifs, line);
// 		if (line.empty()) break;

// 		IFTGraph::IFTEdge edge;
// 		std::stringstream s(line);
// 		getline(s, word, ',');
// 		edge.src = stoi(word);
// 		getline(s, word, ',');
// 		edge.dst = stoi(word);
// 		G.edges.push_back(edge);

// 		G.child_map[edge.src].push_back(edge.dst);
// 	}
// 	ifs.close();
// 	// std::cout << graph << " num edges: " << G.edges.size() << std::endl;
// 	return G;
// }

// void output_graph(std::string graph, std::string method) {
//   /* Parse nodes */
// 	std::ifstream ifs;
// 	ifs.open("../benchmarks/" + graph + "/nodes.txt");
	
//   std::ofstream ofs;
// 	ofs.open("../benchmarks/" + graph + "/" + graph + "_" + method + ".dot");

// 	std::string line, word;
// 	while(!ifs.eof()) {
// 		getline(ifs, line);
// 		if (line.empty()) break;

// 		IFTGraph::IFTNode node;
// 		std::stringstream s(line);
// 		for (int i = 0; i < 4; ++i) {
// 			getline(s, word, ',');

// 			switch (i) {
// 				case 0:
// 					node.node_idx = stoi(word);
// 					break;
// 				case 1: 
// 					node.commit_id = stoi(word);
// 					break;
// 				case 2: 
// 					node.node_str = word;
// 					break;
// 				case 3:
// 					node.nondeterministic = bool(stoi(word));
// 			}
// 		}
// 		G.nodes.push_back(node);
// 	}
// 	ifs.close();

	

// 	ofs << "digraph {\n";

// 	for (auto node : G.nodes) {
// 		std::string color = node.nondeterministic ? "#ef9148" : "#1ABA8B";
// 		ofs << "\"" << node.toString() << "\" [ color = \"" << color 
// 				<< "\", shape = \"box\", label = \"" << node.toString() << "\" ];\n";
// 	}

// 	for (auto edge : G.edges) {
// 		auto src = G.nodes[edge.src];
// 		auto dst = G.nodes[edge.dst];
// 		ofs << "\"" << src.toString() << "\" -> \"" << dst.toString() << "\" ;\n";
// 	}

// 	ofs << "}\n";
// 	ofs.close();
// }
