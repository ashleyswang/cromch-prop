cd graphit/build/bin/

sch_arr=(
  "bfs_hybrid_dense_parallel_cas"
  "bfs_hybrid_dense_parallel_cas_bitvector"
  "bfs_hybrid_dense_parallel_cas_segment"
  "bfs_hybrid_denseforward_serial"
  "bfs_pull_edge_aware_parallel"
  "bfs_pull_parallel_segment"
  "bfs_pull_parallel"
  "bfs_push_parallel_cas"
  "bfs_push_sliding_queue_parallel_cas"
)

for SCHEDULE in ${sch_arr[@]}
do
  echo $SCHEDULE
  python3 graphitc.py -a ../../../graphit_prop.gt -f ../../test/input_with_schedules/${SCHEDULE}.gt -o ../../../graphit_prop_${SCHEDULE}.cpp
  g++ -std=c++14 -I ../../src/runtime_lib/ ../../../graphit_prop_${SCHEDULE}.cpp ../../../utils.cpp -o ../../../graphit_prop_${SCHEDULE}
done