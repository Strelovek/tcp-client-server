#/bin/bash
cd ..
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER:STRING="/usr/bin/g++" .. && make
client/client