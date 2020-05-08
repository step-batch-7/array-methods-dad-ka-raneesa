  
#! /bin/bash

directory=$1
executable=$2
mkdir -p outputs
rm -rf $directory/*.o
gcc -c array.c $directory/*.c
gcc -o outputs/$executable *.o && outputs/$executable
rm -rf *.o