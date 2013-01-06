#!/bin/sh
if [ ! -d "./bin" ]
then
    mkdir bin
fi
if [ ! -d "./lib" ]
then
    mkdir lib
fi

cmake ../src/ -DCMAKE_BUILD_TYPE=Debug
make install
if [ $? -eq 0 ]
then
    cd bin
    ./main
fi
