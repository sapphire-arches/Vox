#!/bin/sh
mkdir bin
mkdir lib
make install
if [ $? -eq 0 ]
then
    cd bin
    ./main
fi
