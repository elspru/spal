AC_INIT([vm], [0.1])
AM_INIT_AUTOMAKE([foreign -Wall subdir-objects])
AC_PROG_CC([clang])
AM_PROG_CC_C_O
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# Custom Define
MY_CFLAGS="-O2 -Iinclude -Wall -Wpedantic -std=c11 \
 -Wunused -Wconversion\
 -Wdouble-promotion   \
 -Waggregate-return -Wextra -I/usr/include/CL"
MY_GCCFLAGS="-O2 -Iinclude -Wall -Wpedantic -std=c11 \
  -Wno-coverage-mismatch\
 -Wlogical-op -Wunused -Wconversion\
 -Wno-aggressive-loop-optimizations -Wunsafe-loop-optimizations\
 -Wdouble-promotion -Wmaybe-uninitialized -lOpenCL -L./library\
 -Waggregate-return -Wextra -I/usr/include/CL"

AC_CHECK_LIB(OpenCL, clGetPlatformIDs, [], [
  echo -e "Error! You need to have OpenCL. Try your (AMD, Intel, Mali) OpenCL\
 SDK\nfor GPU or POCL for CPU. Can include a libOpenCL.so you put in ./library\
\n by using ./configure LDFLAGS=-L./library/"
  exit   -1
])           
AC_CHECK_LIB(OpenCL, clGetDeviceIDs)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_TIME

# Checks for typedefs and compiler characteristics.
AC_C_BIGENDIAN
AC_TYPE_UID_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_PROG_RANLIB
AM_PROG_AR

AC_CHECK_HEADERS(assert.h stdio.h string.h stdint.h)
AC_MSG_CHECKING(for usleep)
AH_TEMPLATE(HAVE_USLEEP)
AC_EGREP_HEADER(usleep, unistd.h, is_usleep=yes, is_usleep=no)
if test $is_usleep = yes; then
  AC_DEFINE(HAVE_USLEEP)
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

# Set localized define flags enable verbosity Define
AC_ARG_ENABLE([verbosity],[    --enable-verbosity    Enable message verbosity])

if test "x$enable_verbosity" = xyes; then
        MY_CFLAGS+=" -DVERBOSITY"
fi

AC_SUBST(MY_CFLAGS)
AC_OUTPUT
