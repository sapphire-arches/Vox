#!/bin/sh
if [ ! -d "./bin" ]
then
    mkdir bin
fi
if [ ! -d "./lib" ]
then
    mkdir lib
fi
if [ ! -e "Makefile" ]
then
    cmake ../src/
fi

make install
if [ $? -eq 0 ]
then
    cd bin
    ./main
fi
