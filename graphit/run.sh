GRAPH=$2
ITER=$1
EX=$3

for (( i=0; i<$ITER; i++ ))
do 
  ./${EX} ${GRAPH} 1
done
