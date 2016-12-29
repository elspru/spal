#!/bin/bash
rm ./*.c
rm ./*.h
rm ./*.cl
make clean
./configure
make
valgrind -q binary/spal
