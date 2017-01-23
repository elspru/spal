#!/bin/bash
FILES="program/parallel/composition_population.cl program/dictionary.c \
      program/seed.c  program/opencl_programmer.c program/seed.h program/spal.c \
      program/spal_compile.c \
      program/dictionary.h program/genericOpenCL.c program/genericOpenCL.h program/spal.h \
      program/hello.c program/encoding.c program/clprobe.c program/spal_dictionary.c\
      program/parallel/quiz_population.cl"
  
for i in $FILES
do
  clang-format "$i" > tmp;
  mv tmp "$i";
done
