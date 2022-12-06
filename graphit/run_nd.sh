# num_nd=$1

# for num_nd in "2000" "3000" "4000" "5000" "6000" "7000" "8000"
for num_nd in "1000"
do
  for i in {1..20}
  do
    ./graphit_prop ${num_nd}/${i}
  done > gt_${num_nd}.txt
done