GRAPH=$1

cd ../graphit/build/bin/
python3 graphitc.py -f ../../../module/graphit_prop_module.gt -o ../../../../cpp/include/gt_module.h
# g++ -std=c++14 -I ../../src/runtime_lib/ ../../../graphit_prop.cpp ../../../utils.cpp -o ../../../graphit_prop
