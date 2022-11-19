from collections import namedtuple

class IFTGraph:
  IFTNode = namedtuple("IFTNode", ["idx", "commit_id", "node_str", "nondeterministic"])
  IFTEdge = namedtuple("IFTEdge", ["src", "dst"])

  def __init__(self):
    self.nodes = []
    self.edges = []

  def get_nondeterministic_nodes(self): 
    return [n.idx for n in self.nodes if n.nondeterministic]