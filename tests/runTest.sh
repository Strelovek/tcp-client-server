#/bin/bash
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER:STRING="/usr/bin/g++" .. && make
./runtests