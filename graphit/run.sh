GRAPH=$1
ITER=$2

for (( i=0; i<$ITER; i++ ))
do 
  ./graphit_prop ${GRAPH} 1
done
