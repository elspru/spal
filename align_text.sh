#!/bin/bash
FILES="code/parallel/composition_population.cl code/dictionary.c \
      code/seed.c  code/opencl_programmer.c code/seed.h code/spal.c \
      code/spal_compile.c \
      code/dictionary.h code/genericOpenCL.c code/genericOpenCL.h code/spal.h \
      code/hello.c code/encoding.c code/clprobe.c\
      code/parallel/quiz_population.cl"
  
for i in $FILES
do
  clang-format "$i" > tmp;
  mv tmp "$i";
done
