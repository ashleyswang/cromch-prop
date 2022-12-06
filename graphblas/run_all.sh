ITERS=$1

# for BENCHMARK in "mt-matmul" "mt-vvadd" "padd" "pmp" "qsort" "vsra"
# for BENCHMARK in "median" "multiply" "spmv" "towers"
for BENCHMARK in "mm" "vvadd"
do
  ./run.sh $BENCHMARK $ITERS > time_$BENCHMARK
done
