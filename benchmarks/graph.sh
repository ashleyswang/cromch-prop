BENCHMARK=$1;
METHOD=$2;

sfdp -Tpng ${BENCHMARK}/graphs/${BENCHMARK}_${METHOD}.dot -o $BENCHMARK/graphs/${BENCHMARK}_${METHOD}.jpg;