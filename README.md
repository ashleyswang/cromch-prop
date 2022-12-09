# Cromch Node Determinism Propagation Methods

## Getting Benchmark Info

1. In the Cromch program, run the following code for the desired benchmark and save the output to a file (without other program outputs).
```
void print_graph_info() {
    foreach (i, vert; ift_graph.nodes) {
        writefln("%s %d", vert.toString(), (vert.flags & IFTGraphNode.Flags.Nondeterministic) > 0);
    }

    foreach (i, edge; ift_graph.edges) {
        writefln("%s -> %s", edge.src.toString(), edge.dst.toString());
    }
}
```

2. Do `cd py` and run `graph_csv.py` using the Cromch output file as the input. This will generate a `nodes.txt`, `edges.el`, and `info.txt` file used for the other propagation methods. 
```
python3 graph_csv.py <cromch_output.txt> ../benchmarks/<benchmark_name>
```

---

## Running C++ Propagation Methods
1. Do `cd cpp` and run `make`. 
2. Run `propagate_flags`. 
```
./propagate_flags <benchmark_name> <propagation_method> <options>
```
Propagation Methods:
- `iter`: single-threaded BFS
- `recur`: sing-threaded DFS
- `multi`: multithreaded BFS
- `multir`: multithreaded DFS

Options: 
- `--repeat #`: print propagation execution time for # iterations (default 0)
- `--graph`: output `.dot` file for propagated graph
- `--output`: print index of all nondeterministic nodes after propagation

---

## Running GraphBLAS/LAGraph
1. Make sure GraphBLAS and LAGraph is installed on your machine. 
2. Do `cd graphblas`. Run `./build.sh` to compile the program. 
3. Run main. The program will print execution times for `num_iterations` of graphBLAS. If `output_file` is given, the indices of all nondeterministic nodes after propagation will be written to `output_file`.
```
./main <benchmark_name> <num_iterations> <output_file>
```

---

## Running GraphIt
1. Do `cd graphit`. Install GraphIt submodule in current directory (in own `graphit` subdirectory). 
2. Run `./build.sh` to compile the program. 
3. Run `./graphit_prop <benchmark_name>` for timing of single execution. To print out indices of all nondeterministic nodes after propagation uncomment line 49 from `graphit_prop.gt`. 

---

## Running NetworkX
1. Install NetworkX. 
2. Do `cd py` and run `python3 nx_propagate.py <options>`.

Options: 
- `--graph`: benchmark name
- `--method` : propagation method (`bfs` or `dfs`)
- `--iter`: print execution times for X iterations
- `--graph`: output `.dot` graph
- `--ndout`: writes indicies of nondeterministic nodes after propagation to `<name>_nd_out.txt`. 


