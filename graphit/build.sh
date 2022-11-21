GRAPH=$1

cd graphit/build/bin/
python3 graphitc.py -f ../../../graphit_prop.gt -o ../../../graphit_prop.cpp
g++ -std=c++14 -I ../../src/runtime_lib/ ../../../graphit_prop.cpp ../../../utils.cpp -O3 -o ../../../graphit_prop
