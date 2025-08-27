#!/bin/bash


if [ -d "build" ]; then
    cd build
if [ ! $# -eq 1 ] && [ "$1" == "-r" ]; then
    cmake ..
fi
    make 
    ./pulse64
    cd ..
else 
    mkdir build
    cd build 
    cmake ..
    make 
    ./pulse64  
    cd ..
fi
