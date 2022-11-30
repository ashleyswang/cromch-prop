from collections import deque
from ift import IFTGraph

def dfs_edges(G, source=None, depth_limit=None):
    """Iterate over edges in a depth-first-search (DFS).

    Perform a depth-first-search over the nodes of `G` and yield
    the edges in order. This may not generate all edges in `G`
    (see `~networkx.algorithms.traversal.edgedfs.edge_dfs`).

    Parameters
    ----------
    G : NetworkX graph

    source : node, optional
       Specify starting node for depth-first search and yield edges in
       the component reachable from source.

    depth_limit : int, optional (default=len(G))
       Specify the maximum search depth.

    Yields
    ------
    edge: 2-tuple of nodes
       Yields edges resulting from the depth-first-search.

    Examples
    --------
    >>> G = nx.path_graph(5)
    >>> list(nx.dfs_edges(G, source=0))
    [(0, 1), (1, 2), (2, 3), (3, 4)]
    >>> list(nx.dfs_edges(G, source=0, depth_limit=2))
    [(0, 1), (1, 2)]

    Notes
    -----
    If a source is not specified then a source is chosen arbitrarily and
    repeatedly until all components in the graph are searched.

    The implementation of this function is adapted from David Eppstein's
    depth-first search function in PADS [1]_, with modifications
    to allow depth limits based on the Wikipedia article
    "Depth-limited search" [2]_.

    See Also
    --------
    dfs_preorder_nodes
    dfs_postorder_nodes
    dfs_labeled_edges
    :func:`~networkx.algorithms.traversal.edgedfs.edge_dfs`
    :func:`~networkx.algorithms.traversal.breadth_first_search.bfs_edges`

    References
    ----------
    .. [1] http://www.ics.uci.edu/~eppstein/PADS
    .. [2] https://en.wikipedia.org/wiki/Depth-limited_search
    """
    if source is None:
        # edges for all components
        nodes = G
    else:
        # edges for components with source
        nodes = source
    visited = set()
    if depth_limit is None:
        depth_limit = len(G)
    for start in nodes:
        if start in visited:
            continue
        visited.add(start)
        stack = [(start, depth_limit, iter(G[start]))]
        while stack:
            parent, depth_now, children = stack[-1]
            try:
                child = next(children)
                if child not in visited:
                    yield parent, child
                    visited.add(child)
                    if depth_now > 1:
                        stack.append((child, depth_now - 1, iter(G[child])))
            except StopIteration:
                stack.pop()

def dfs_multi(G, sources):
    return [x[1] for x in list(dfs_edges(G, sources))]