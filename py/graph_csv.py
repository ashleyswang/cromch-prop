import sys

def read_graph(input_file, output_path):
  data = open(input_file, 'r').readlines()
  nodes = [x.split() for x in data if len(x.split()) == 3]
  edges = [x.split(" -> ") for x in data if len(x.split()) == 5]

  node_out = open(f"{output_path}/nodes.txt", "w")
  nd_node_out = open(f"{output_path}/nd_nodes.txt", "w")

  node_id = 0
  node_dict = {}
  for node in nodes: 
    commit_id, node_str, nondeterministc = node
    commit_id = commit_id.strip("#")

    key = f"#{commit_id} {node_str}"
    if (key not in node_dict): 
      node_dict[key] = node_id
      node_out.write(f"{node_id},{commit_id},{node_str},{nondeterministc}\n")
      if (int(nondeterministc)): nd_node_out.write(f"{node_id}\n")
      node_id += 1
  node_out.close()
  nd_node_out.close()

  edge_out = open(f"{output_path}/edges.el", "w")
  edge_arr = []
  for edge in edges:
    src, dst = edge
    dst = dst.strip()
    if (src in node_dict and dst in node_dict):
      src_idx = node_dict[src]
      dst_idx = node_dict[dst]
      edge_arr.append((src_idx, dst_idx))
    else:
      print(f"node in edge not found: {src} -> {dst}")

  edge_arr.sort()
  for edge in edge_arr:
    edge_out.write(f"{edge[0]} {edge[1]}\n")
  edge_out.close()

if __name__ == "__main__":
  if (len(sys.argv) < 3):
    print("USAGE: python3 graph_csv.py <input_file> <output_path>")
    exit()
  
  read_graph(sys.argv[1], sys.argv[2])
