# num_nd=$1

for num_nd in "500" "1000" "2000" "3000" "4000" "5000" "6000" "7000" "8000"
do
  for i in {1..20}
  do
    ./main ${num_nd}/${i}.txt
  done > gb_${num_nd}.txt
done