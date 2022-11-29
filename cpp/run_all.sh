METHOD=$1
ITERS=$2

for BENCHMARK in "mt-matmul" "mt-vvadd" "padd" "pmp" "qsort" "vsra"
do
  ./propagate_flags $BENCHMARK $METHOD --repeat $ITERS > ${BENCHMARK}.times
done
