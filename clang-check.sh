#!/bin/sh
mkdir build-clang
cd build-clang
cmake ../src/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd ..
find src/ -name "*.cpp" | xargs clang-check -p build-clang
