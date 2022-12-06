# ITERS=$1

# # for BENCHMARK in "mt-matmul" "mt-vvadd" "padd" "pmp" "qsort" "vsra"
# # for BENCHMARK in "median" "multiply" "spmv" "towers"
# for BENCHMARK in "mm" "vvadd"
# do
#   ./run.sh $ITERS $BENCHMARK > time_$BENCHMARK
# done

sch_arr=(
  "bfs_hybrid_dense_parallel_cas"
  "bfs_hybrid_dense_parallel_cas_bitvector"
  "bfs_hybrid_dense_parallel_cas_segment"
  "bfs_hybrid_denseforward_serial"
  "bfs_pull_edge_aware_parallel"
  "bfs_pull_parallel"
  "bfs_pull_parallel_segment"
  "bfs_push_parallel_cas"
  "bfs_push_sliding_queue_parallel_cas"
)


for SCHEDULE in ${sch_arr[@]}
do
  echo $SCHEDULE
  ./run.sh 10 $1 graphit_prop_${SCHEDULE}
  echo ""
done;