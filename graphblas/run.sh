GRAPH=$1
ITER=$2

for (( i=0; i<$ITER; i++ ))
do 
  ./main ${GRAPH} 1
done
