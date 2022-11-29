ITERS=$1

# for BENCHMARK in "mt-matmul" "mt-vvadd" "padd" "pmp" "qsort" "vsra"
for BENCHMARK in "pmp" "qsort" "vsra"
do
  python3 nx_propagate.py --iter $ITERS --graph $BENCHMARK > ${BENCHMARK}.times
done
