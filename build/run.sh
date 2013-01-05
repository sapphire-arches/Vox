#!/bin/sh
make
if [ $? -eq 0 ]
then
    cd bin
    ./main
fi
