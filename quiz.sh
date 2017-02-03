#!/bin/bash
rm ./*.c
rm ./*.h
rm ./*.cl
make clean
./configure
make
valgrind -q binary/spal probe/trop.pya
valgrind -q binary/spal_dictionary probe/pyashWords.txt probe/pyashWords.h
