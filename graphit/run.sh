ITER=$1
GRAPH=$2
# EX=$3

for (( i=0; i<$ITER; i++ ))
do 
  ./graphit_prop ${GRAPH} 1
done
