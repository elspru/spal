#!/bin/bash
rm ./*.c
rm ./*.h
rm ./*.cl
make clean
./configure
make
valgrind -q binary/spal probe/trop.pya
#strace binary/spal probe/trop.pya
valgrind -q binary/spal_dictionary probe/pyashWords.txt probe/pyashWords.h
valgrind -q binary/spal_translation probe/en.kwon probe/trop.byin
