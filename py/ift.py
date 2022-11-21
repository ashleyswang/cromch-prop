from collections import namedtuple

class IFTGraph:
  class IFTNode:
    def __init__(self, idx, commit_id, node_str, nondeterministic):
      self.idx = idx
      self.commit_id = commit_id
      self.node_str = node_str
      self.nondeterministic = nondeterministic

  IFTEdge = namedtuple("IFTEdge", ["src", "dst"])

  def __init__(self):
    self.nodes = []
    self.edges = []

  def get_nondeterministic_nodes(self): 
    return [n.idx for n in self.nodes if n.nondeterministic]