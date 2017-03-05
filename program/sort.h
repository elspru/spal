#ifndef SORT_H
#define SORT_H


#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#ifndef __has_extension
#define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif
#ifndef __has_feature      // Optional of course.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif
#ifndef __has_builtin      // Optional of course.
#define __has_builtin(x) 0 // Compatibility with non-clang compilers.
#endif

typedef unsigned int uint;

#if __has_builtin(__builtin_shufflevector)
#define shuffle __builtin_shufflevector
#endif
#if defined(_MSC_VER)
/* Microsoft C/C++-compatible compiler */
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
/* GCC-compatible compiler, targeting x86/x86-64 */
#include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON__)
/* GCC-compatible compiler, targeting ARM with NEON */
#include <arm_neon.h>
#elif defined(__GNUC__) && defined(__IWMMXT__)
/* GCC-compatible compiler, targeting ARM with WMMX */
#include <mmintrin.h>
#elif (defined(__GNUC__) || defined(__xlC__)) &&                               \
    (defined(__VEC__) || defined(__ALTIVEC__))
/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#include <altivec.h>
#elif defined(__GNUC__) && defined(__SPE__)
/* GCC-compatible compiler, targeting PowerPC with SPE */
#include <spe.h>
#endif

#if __has_feature(attribute_ext_vector_type)
// This code will only be compiled with the -std=c++11 and -std=gnu++11
// options, because rvalue references are only standardized in C++11.
typedef cl_uchar uint8_t;
typedef cl_ushort uint16_t;
typedef cl_uint uint32_t;
typedef cl_ulong uint64_t;
typedef cl_short4 v4si;
typedef cl_uchar16 v16uc;
// typedef cl_ushort16 v16us;
typedef unsigned int v16us __attribute__((ext_vector_type(16)));
typedef cl_ushort8 v8us;
typedef unsigned int v4us __attribute__((ext_vector_type(4)));
// typedef cl_ushort4 v4us;
#else
typedef cl_uchar uint8_t;
typedef cl_ushort uint16_t;
typedef cl_uint uint32_t;
typedef cl_ulong uint64_t;
typedef cl_short4 v4si;
typedef cl_uchar16 v16uc;
typedef cl_ushort16 v16us;
typedef cl_ushort8 v8us;
typedef cl_ushort4 v4us;
#endif

#define V8US_LONG 16
/*#define NULL 0*/


#define TRUE 1
#define FALSE 0

#endif
