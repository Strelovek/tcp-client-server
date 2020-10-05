#/bin/bash
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER:STRING="/usr/bin/g++" .. && make
for number in 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150
do 
./client 
done

