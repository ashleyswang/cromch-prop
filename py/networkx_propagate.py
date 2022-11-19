import networkx as nx
import sys

def read_graph(benchmark):
  G = nx.DiGraph()

  node_data = open(f"../benchmarks/{benchmark}/nodes.txt", 'r').readlines()
  node_arr = []
  for line in node_data: 
    idx, commit_id, node_str, nondeterministic = line.split(',')
    node_arr.append((idx, {
        "commit_id" : commit_id, 
        "node_str" : node_str, 
        "nondeterministic" : bool(nondeterministic)
      }))
  G.add_nodes_from(node_arr)

  edge_data = open(f"../benchmarks/{benchmark}/edges.txt", 'r').readlines()
  for line in edge_data:
    src, dst = [int(i) for i in line.split(',')]
    G.add_edge(src, dst)

  return G

  

if __name__ == "__main__":
  if (len(sys.argv) < 2):
    print("USAGE: python3 networkx_propagate.py <benchmark>")
    exit()
  
  G = read_graph(sys.argv[1])