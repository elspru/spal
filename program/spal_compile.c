/*SPEL machine programmer
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

#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "agree.h"
#include "dialogue.h"
#include "genericOpenCL.h"
#include "seed.h"

#define VALGRIND
#define NEWSPAPER_LONG 0x10
uint8_t newspaper_indexFinger = 0;
const uint16_t newspaper_byte_magnitude = NEWSPAPER_LONG * TABLET_BYTE_LONG;
// v16us newspaper[NEWSPAPER_LONG] = {0};

void text_file_addenda(const int text_long, const char *text,
                       const char *filename) {
  FILE *out = fopen(filename, "a");
  assert(out != NULL);
  int written_text_long = fprintf(out, "%s", text);
  printf("text_long %X \n", text_long);
  printf("written_text_long %X \n", written_text_long);
  assert(written_text_long >= text_long);
  int result = fclose(out);
  assert(result == 0);
}

void newspaper_print(const uint16_t newspaper_indexFinger,
                     const v16us *newspaper) {
  uint16_t indexFinger = 0;
  char text[TABLET_LONG * WORD_LONG] = "";
  uint16_t text_long = TABLET_LONG * WORD_LONG;
  printf("newspaper %X\n", newspaper_indexFinger);
  for (; indexFinger < newspaper_indexFinger; ++indexFinger) {
    printf("%X %X %X %X  %X %X %X %X  %X %X %X %X  %X %X %X %X\n",
           newspaper[indexFinger].s0, newspaper[indexFinger].s1,
           newspaper[indexFinger].s2, newspaper[indexFinger].s3,
           newspaper[indexFinger].s4, newspaper[indexFinger].s5,
           newspaper[indexFinger].s6, newspaper[indexFinger].s7,
           newspaper[indexFinger].s8, newspaper[indexFinger].s9,
           newspaper[indexFinger].sA, newspaper[indexFinger].sB,
           newspaper[indexFinger].sC, newspaper[indexFinger].sD,
           newspaper[indexFinger].sE, newspaper[indexFinger].sF);
    tablet_translate(newspaper[indexFinger], &text_long, text);
    printf("tablet %s\n", text);
  }
}

void probe() {
  // probe word to number translation
  uint16_t word_number = 0;
  v16us newspaper[NEWSPAPER_LONG] = {0};
  uint16_t newspaper_indexFinger = 0;
  // probe short grammar
  const char short_grammar_word[] = "li";
  const uint8_t short_grammar_word_long = (uint8_t)strlen(short_grammar_word);
  word_number_encode(short_grammar_word_long, short_grammar_word, &word_number);
  printf("word_number %X\n", word_number);
  agree(word_number == 0x17E, "ksashfakhlishsiphwapli", &newspaper_indexFinger,
        newspaper);
  // probe long grammar
  // probe short root
  // probe long root
  newspaper_print(newspaper_indexFinger, newspaper);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no input filename\n");
    return 0;
  } // else if (argc < 3) {
  //  printf("no produce filename\n");
  //}
  // Generic Algorithm:
  // load text from file
  // convert text to binary encoding
  // convert binary to OpenCL source code

  char filename[64] = "";
  const char *input_filename = argv[1];
  char recipe_text[MAXIMUM_PAPER_LONG] = {0};
  uint16_t recipe_text_magnitude = MAXIMUM_PAPER_LONG;
  // load text from file
  // const char *recipe_text =
  //    "kratta krathnimna li hcantlattyehka hsactu zrondofi fe";
  // const uint16_t recipe_text_magnitude = (uint16_t)strlen(recipe_text);
  uint16_t recipe_magnitude = 5;
  paper_read(input_filename, 0, &recipe_text_magnitude, recipe_text);
  v16us recipe[8] = {0};
  uint16_t text_remainder = 0;
  uint8_t tablet_indexFinger = 0;
  uint16_t recipe_byte_magnitude =
      (uint16_t)(recipe_magnitude * TABLET_LONG * WORD_THICK);
  memset(recipe, 0, (size_t)(recipe_byte_magnitude));
  printf(" te1 \n");
  // convert text to binary encoding
  assert(text_remainder == 0);
  printf(" te2 \n");
  text_encoding(recipe_text_magnitude, recipe_text, &recipe_magnitude, recipe,
                &text_remainder);
  printf(" yep \n");
  // convert binary to OpenCL source code
  // print binary

  uint16_t recipe_indexFinger = 0;
  for (recipe_indexFinger = 0; recipe_indexFinger < recipe_magnitude;
       ++recipe_indexFinger) {
    printf("\nrecipe[%X]", recipe_indexFinger);
    for (tablet_indexFinger = 0; tablet_indexFinger < (TABLET_LONG);
         ++tablet_indexFinger) {
      if (tablet_indexFinger % 0x10 == 0)
        printf("\n");
      printf("%04X ",
             (uint)v16us_read(tablet_indexFinger, recipe[recipe_indexFinger]));
    }
  }
  printf("\n");

  // uint64_t code_name = 0;
  // code_name_derive((uint8_t)recipe_magnitude, recipe, &code_name);
  // printf("code_name 64bit %016lX\n", code_name);
  const uint16_t max_produce_text_long = 256;
  uint16_t produce_text_long = max_produce_text_long;
  char produce_text[256] = "";
  memset(produce_text, 0, max_produce_text_long);
  uint16_t filename_long = 64;
  uint16_t gross_filename_long = 64;
  char gross_filename[64] = "";
  uint16_t file_sort = 0;
  uint16_t gross_text_long = 0;
  for (recipe_indexFinger = 0; recipe_indexFinger < recipe_magnitude;
       ++recipe_indexFinger) {
    code_opencl_translate(recipe_magnitude, &(recipe[recipe_indexFinger]),
                          &produce_text_long, produce_text + gross_text_long,
                          &filename_long, filename, &file_sort);
    // text_file_addenda(produce_text_long, produce_text, gross_filename);
    gross_text_long += produce_text_long;
    produce_text_long = max_produce_text_long - gross_text_long;
    printf("recipe %X produce text '%s' produce_text_long %X\n",
           recipe_indexFinger, produce_text, produce_text_long);
  }

  derive_filename(filename_long, filename, file_sort, &produce_text_long,
                  gross_filename);
  //  code_opencl_translate(recipe_magnitude, &(recipe[1]), &produce_text_long,
  //                        produce_text + gross_text_long, &filename_long,
  //                        filename, &file_sort);
  //  gross_text_long += produce_text_long;
  //  produce_text_long = max_produce_text_long - gross_text_long;
  //  code_opencl_translate(recipe_magnitude, &(recipe[2]), &produce_text_long,
  //                        produce_text + gross_text_long, &filename_long,
  //                        filename, &file_sort);
  // get gross filename based on file sort and filename

  // create file if not existing
  // append to file buffer
  printf("text_long %X text '%s' filename_long %X filename '%s' file_sort %X "
         "gross_filename %s\n",
         produce_text_long, produce_text, filename_long, filename, file_sort,
         gross_filename);

  derive_filename(filename_long, filename, file_sort, &gross_filename_long,
                  gross_filename);
  text_file_addenda(gross_text_long, produce_text, gross_filename);
  probe();
  return 0;
}
