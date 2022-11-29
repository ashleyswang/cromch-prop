TRACE=$1
METHOD=$2
ITER=$3

for (( i=0; i<$ITER; i++ ))
do 
  ./propagate_flags $TRACE $METHOD --repeat 1
done
