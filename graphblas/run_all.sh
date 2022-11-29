ITERS=$1

for BENCHMARK in "mt-matmul" "mt-vvadd" "padd" "pmp" "qsort" "vsra"
do
  ./run.sh $BENCHMARK $ITERS > time_$BENCHMARK
done
