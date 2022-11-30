cd graphit/build/bin/
python3 graphitc.py -f ../../../graphit_prop_$1.gt -o ../../../graphit_prop_$1.cpp
g++ -std=c++14 -I ../../src/runtime_lib/ ../../../graphit_prop_$1.cpp ../../../utils.cpp -o ../../../graphit_prop_$1
