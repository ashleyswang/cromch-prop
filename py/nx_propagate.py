import argparse
import networkx as nx
import timeit
from ift import IFTGraph
from nx_bfs import bfs_multi
from nx_dfs import dfs_multi

def read_graph(benchmark):
  G = IFTGraph()

  node_data = open(f"../benchmarks/{benchmark}/nodes.txt", 'r').readlines()
  for line in node_data: 
    idx, commit_id, node_str, nondeterministic = line.split(',')
    G.nodes.append(IFTGraph.IFTNode(int(idx), 
                                    int(commit_id), 
                                    node_str, 
                                    bool(int(nondeterministic))))

  edge_data = open(f"../benchmarks/{benchmark}/edges.el", 'r').readlines()
  for line in edge_data:
    src, dst = [int(i) for i in line.split(' ')]
    G.edges.append(IFTGraph.IFTEdge(src, dst))

  return G

def output_graph(G : IFTGraph, benchmark):
  ofs = open(f"../benchmarks/{benchmark}/graphs/{benchmark}_nx.dot", "w")
  ofs.write("digraph {\n")
  
  for node in G.nodes:
    node_str = f"#{node.commit_id} {node.node_str}"
    color = "#ef9148" if node.nondeterministic else "#1ABA8B"
    ofs.write(f'"{node_str}" [ color = "{color}", shape = "box", label = "{node_str}" ];\n')

  for edge in G.edges:
    src = G.nodes[edge.src]
    dst = G.nodes[edge.dst]
    ofs.write(f'"#{src.commit_id} {src.node_str}" -> "#{dst.commit_id} {dst.node_str}" ;\n')

  ofs.write("}\n")
  ofs.close()


def to_nxgraph(ift_graph):
  G = nx.DiGraph()
  G.add_nodes_from([i for i in range(len(ift_graph.nodes))])
  G.add_edges_from([(e.src, e.dst) for e in ift_graph.edges])
  return G

def propagate_flags(G, traversal): 
  nx_graph = to_nxgraph(G)
  nd_nodes = G.get_nondeterministic_nodes()

  prop_nodes = traversal(nx_graph, nd_nodes)
  for nidx in prop_nodes:
    G.nodes[nidx].nondeterministic = True

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--graph", default="vsra")
  parser.add_argument("--method", default="bfs")
  parser.add_argument("--iter", default=1, type=int)
  parser.add_argument("--output", default=False)
  args = parser.parse_args()

  traversal = dfs_multi if (args.method == "dfs") else bfs_multi
    
  if (args.output):
    G = read_graph(args.graph)
    propagate_flags(G, traversal)
    # output_graph(G, args.graph)
    for node in G.nodes:
      if node.nondeterministic:
        print(node.idx)
  else: 
    for _ in range(args.iter):
      G = read_graph(args.graph)
      t = timeit.timeit(lambda: propagate_flags(G, traversal), number=1)
      print(t*1000)