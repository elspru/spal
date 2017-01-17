#!/bin/bash
rm ./*.c
rm ./*.h
rm ./*.cl
make clean
./configure
make
valgrind -q binary/spal_dictionary probe/gramWords-core.txt probe/gramDict.txt
valgrind -q binary/spal
