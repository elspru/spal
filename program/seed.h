/*SPEL virtual machine
Copyright (C) 2016  Logan Streondj

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

contact: streondj at gmail dot com
*/
#ifndef SEED_H
#define SEED_H

#include "pyashWords.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
#define MAX_WRITE_MEMORY 0x8000 // GPU comput unit memory limit

#define VECTOR_THICK_BEGIN 0x8
#define VECTOR_THICK_MASK 0x700
#define VECTOR_THICK_1 0
#define VECTOR_THICK_2 1
#define VECTOR_THICK_4 2
#define VECTOR_THICK_8 3
#define VECTOR_THICK_16 4
#define VECTOR_THICK_3 7

#define MAXIMUM_WORD_SERIES_LONG 0x10
#define WORD_THICK 2
#define GLOTTAL_STOP 0xC
#define MAX_LONG 0xFFU
#define INDEPENDENTCLAUSE_LONG 0xFF
#define WORD_LONG 0x05
#define CODE_WORD_TIDBIT_LONG 0x10
#define ERROR_BINARY 0
#define LONG_ROOT 1
#define SHORT_ROOT 2
#define LONG_GRAMMAR 3
#define SHORT_GRAMMAR 4
#define SHORT_ROOT_DENOTE 0
#define QUOTE_DENOTE 0x1D
#define QUOTE_DENOTE_MASK 0x1F
#define SHORT_GRAMMAR_DENOTE 0x1E
#define SHORT_GRAMMAR_DENOTE_MASK 0x1F
#define CONSONANT_ONE_THICK 5
#define CONSONANT_ONE_MASK 0x1F
#define SHORT_SORT_MASK 0x7
#define LONG_SORT_MASK 0x1F
#define SHORT_ROOT_CONSONANT_ONE_MASK 0xF8
#define SHORT_ROOT_CONSONANT_ONE_BEGIN 0x3
#define SHORT_ROOT_VOWEL_BEGIN 0x8
#define SHORT_ROOT_VOWEL_MASK 0x700
#define SHORT_ROOT_TONE_BEGIN 11
#define SHORT_ROOT_TONE_MASK 0x1800
#define SHORT_ROOT_CONSONANT_THREE_BEGIN 13
#define SHORT_ROOT_CONSONANT_THREE_MASK 0xE000
#define LONG_GRAMMAR_DENOTE 7
#define LONG_GRAMMAR_DENOTE_MASK 0x7
#define LONG_GRAMMAR_CONSONANT_ONE_MASK 0xF8
#define LONG_GRAMMAR_CONSONANT_ONE_BEGIN 0x3
#define LONG_GRAMMAR_CONSONANT_TWO_MASK 0x700
#define LONG_GRAMMAR_CONSONANT_TWO_BEGIN 0x8
#define LONG_GRAMMAR_VOWEL_BEGIN 0xB
#define LONG_GRAMMAR_VOWEL_MASK 0x3800
#define LONG_GRAMMAR_TONE_BEGIN 0xE
#define LONG_GRAMMAR_TONE_MASK 0xC000
#define SHORT_GRAMMAR_CONSONANT_ONE_BEGIN 0x5
#define SHORT_GRAMMAR_CONSONANT_ONE_MASK 0x3E0
#define SHORT_GRAMMAR_VOWEL_BEGIN 0xA
#define SHORT_GRAMMAR_VOWEL_MASK 0x1C00
#define SHORT_GRAMMAR_TONE_BEGIN 0xD
#define SHORT_GRAMMAR_TONE_MASK 0x6000
#define LONG_ROOT_CONSONANT_ONE_BEGIN 0x0
#define LONG_ROOT_CONSONANT_ONE_MASK 0x1F
#define LONG_ROOT_CONSONANT_TWO_BEGIN 0x5
#define LONG_ROOT_CONSONANT_TWO_MASK 0xE0
#define LONG_ROOT_VOWEL_BEGIN 0x8
#define LONG_ROOT_VOWEL_MASK 0x700
#define LONG_ROOT_TONE_BEGIN 11
#define LONG_ROOT_TONE_MASK 0x1800
#define LONG_ROOT_CONSONANT_THREE_BEGIN 13
#define LONG_ROOT_CONSONANT_THREE_MASK 0xE000
#define CODE_SORT_MASK 0x7
#define BANNER_THICK 3
#define CONSONANT_TWO_THICK 3
#define VOWEL_THICK 3
#define TONE_THICK 2
#define TABLET_BYTE_LONG 0x20
#define TABLET_LONG 0x10
#define CODE_NAME_WORD_LONG 0x4
#define TABLET_WORD_LONG 0xF
#define MAX_INDEPENDENTCLAUSE_TABLET 0x4
#define QUOTED_DENOTE 0x1D
#define SINGLE_BYTE_QUOTED 0x0
#define TWO_BYTE_QUOTED 0x1
#define FOUR_BYTE_QUOTED 0x2
#define EIGHT_BYTE_QUOTED 0x3
#define SIXTEEN_BYTE_QUOTED 0x4
#define SILENCE_GLYPH '.'
#define SILENCE_GLYPH_LONG 1

// quote sorts
#define SORT_DENOTE_BEGIN 0xD
#define SORT_DENOTE_MASK 0xE000
#define LETTER_SORT_DENOTE 0
#define WORD_SORT_DENOTE 1
#define INDEPENDENT_CLAUSE_SORT_DENOTE 2
#define BINARY_SORT_DENOTE 3
#define UINT_SORT_DENOTE 4
#define INT_SORT_DENOTE 5
#define FLOAT_SORT_DENOTE 6
#define CEREMONY_SORT_DENOTE 6

// scalar thick
#define SCALAR_THICK_BEGIN 0xB
#define SCALAR_THICK_MASK 0x1800
#define EIGHT_TIDBIT_SCALAR_THICK 0
#define SIXTEEN_TIDBIT_SCALAR_THICK 1
#define THIRTY_TWO_TIDBIT_SCALAR_THICK 2
#define SIXTY_FOUR_TIDBIT_SCALAR_THICK 3

#define POSTURE_TIDBIT 14
#define SCENE_TIDBIT 11
#define NAME_TIDBIT 5
#define REGION_TIDBIT 6
#define VECTOR_THICK_TIDBIT 8
#define SCALAR_THICK_TIDBIT 11
#define SORT_DENOTE_TIDBIT 13
#define SOURCE_CASE 0
#define WAY_CASE 1
#define DESTINATION_CASE 2
#define LOCATION_CASE 3
#define BASE_CONTEXT 0
#define SPACE_CONTEXT 1
#define GENITIVE_CONTEXT 2
#define DISCOURSE_CONTEXT 3
#define SOCIAL_CONTEXT 4
#define SURFACE_CONTEXT 5
#define INTERIOR_CONTEXT 6
#define TIME_CONTEXT 7

#define QUOTED_LITERAL_XOR_ADDRESS_BEGIN 8
#define QUOTED_LITERAL 0
#define QUOTED_LITERAL_BEGIN 8
#define QUOTED_ADDRESS 1
#define QUOTED_INTEGER_BEGIN 9
#define QUOTED_GLYPH_THICK_BEGIN 0xA
#define QUOTED_CLASS_BEGIN 0xC

#define TRUE 1
#define FALSE 0
#define QUOTED_WORD_LONG 2
#define MAX_GRAMMATICALCASE_INE_INDEPENDENTCLAUSE 8
#define HOOK_LIST_LONG 3
#define HOOK_LIST_THICK 8
#define BINARY_PHRASE_LIST_LENGTH 0x10
#define VERB_INDEXFINGER 3
#define ACCUSATIVE_INDEXFINGER 2
#define INSTRUMENTAL_INDEXFINGER 1
#define DATIVE_INDEXFINGER 0

#define TEXT_CLASS 0x0
#define NUMBER_CLASS 0x1
#define INTEGER_CLASS 0x2
#define FLOAT_CLASS 0x3
#define RATIONAL_CLASS 0x4
#define COMPLEX_CLASS 0x5

#define UNSIGNED_CHAR_QUOTED 0x009D
#define SIGNED_CHAR_QUOTED 0x029D
#define SHORT_NUMBER_QUOTED 0x143D

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

void delete_empty_glyph(const uint16_t size, const char *letter,
                        uint16_t *fresh_size, char *tidyLetter);
void derive_first_word(const uint8_t size, const char *independentClause,
                       uint8_t *fresh_size, char *word);
void code_ACC_word_PL(const uint8_t ACC_GEN_size,
                      const char *ACC_independentClause, uint8_t *DAT_GEN_size,
                      uint16_t *DAT_code_independentClause,
                      uint8_t *DAT_GEN_remainder);
void word_number_encode(const uint8_t word_size, const char *word,
                        uint16_t *number);

void text_copy(const uint8_t size, const char *ACC_text, char *DAT_text);

void tablet_encoding(const uint8_t code_text_size, const uint16_t *code_text,
                     uint8_t *tablet_size, uint16_t *tablet,
                     uint8_t *remainder);
void independentClause_encoding(const uint16_t text_size, const char *text,
                                uint8_t *tablet_size, v16us *tablet,
                                uint16_t *remainder);
void text_encoding(const uint16_t text_size, const char *text,
                   uint16_t *tablet_size, v16us *tablet,
                   uint16_t *text_remainder);
void play(const v4us coded_name, v8us *hook_list);
void burden_hook_list(const uint8_t tablet_size, const v16us *tablet,
                      uint8_t *tablet_indexFinger, v4us *coded_name,
                      v8us *hook_list);
void play_independentClause(const uint8_t tablet_size, const v16us *tablet,
                            v4us *coded_name, v8us *hook_list);
void play_text(const uint16_t tablet_size, const v16us *tablet,
               v4us *coded_name, v8us *hook_list);
void derive_code_name(const uint8_t tablet_magnitude, const v16us *tablet,
                      v4us *code_name);
void code_name_derive(const uint8_t tablet_magnitude, const v16us *tablet,
                      uint64_t *code_name);

uint16_t v16us_read(const uint8_t indexFinger, const v16us vector);
uint64_t v4us_uint64_translation(const v4us vector);
void code_opencl_translate(const uint16_t recipe_magnitude, const v16us *recipe,
                           uint16_t *text_long, char *produce_text,
                           uint16_t *filename_long, char *filename,
                           uint16_t *file_sort);

void derive_filename(const uint16_t filename_long, const char *filename,
                     const uint16_t file_sort, uint16_t *gross_filename_long,
                     char *gross_filename);

void tablet_translate(const v16us tablet, uint16_t *text_long, char *text);
#endif
