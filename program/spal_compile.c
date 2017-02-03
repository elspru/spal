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
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _(String) gettext(String)

#include "agree.h"
#include "dialogue.h"
#include "genericOpenCL.h"
#include "seed.h"

#define VALGRIND
#define NEWSPAPER_LONG 0x10
// v16us newspaper[NEWSPAPER_LONG] = {0};

void newspaper_print(const uint16_t newspaper_indexFinger,
                     const v16us *newspaper) {
  uint16_t indexFinger = 0;
  char text[TABLET_LONG * WORD_LONG] = "";
  uint16_t text_long = TABLET_LONG * WORD_LONG;
  printf("%s:%d:\tnewspaper %X\n\t", __FILE__, __LINE__, newspaper_indexFinger);
  for (; indexFinger < newspaper_indexFinger; ++indexFinger) {
    printf("%04X %04X %04X %04X  %04X %04X %04X %04X  %04X %04X %04X %04X  "
           "%04X %04X %04X %04X\n",
           newspaper[indexFinger].s0, newspaper[indexFinger].s1,
           newspaper[indexFinger].s2, newspaper[indexFinger].s3,
           newspaper[indexFinger].s4, newspaper[indexFinger].s5,
           newspaper[indexFinger].s6, newspaper[indexFinger].s7,
           newspaper[indexFinger].s8, newspaper[indexFinger].s9,
           newspaper[indexFinger].sA, newspaper[indexFinger].sB,
           newspaper[indexFinger].sC, newspaper[indexFinger].sD,
           newspaper[indexFinger].sE, newspaper[indexFinger].sF);
    tablet_translate(newspaper[indexFinger], &text_long, text);
    printf("\t%s\n", text);
    printf("\tTODO translate to local locale\n");
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
  // printf("word_number %X\n", word_number);
  agree(word_number == 0x17E, "ksashfakhlishsiphwapli", &newspaper_indexFinger,
        newspaper);
  // probe long grammar
  // probe short root
  // probe long root
  newspaper_print(newspaper_indexFinger, newspaper);
}

int main(int argc, char *argv[]) {
  char language_code[16] = {0};
  uint8_t language_code_long = 16;
  region_language_identity(&language_code_long, &language_code);
  printf("%s:%d\tLC_CTYPE: %s %d\n", __FILE__, __LINE__, language_code,
         language_code_long);
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

#define MAXIMUM_PRODUCE_TEXT_LONG 0x1000
  uint16_t produce_text_long = MAXIMUM_PRODUCE_TEXT_LONG;
  char produce_text[MAXIMUM_PRODUCE_TEXT_LONG] = "";
  memset(produce_text, 0, MAXIMUM_PRODUCE_TEXT_LONG);
#define MAXIMUM_FILENAME_LONG 0x40
  const uint16_t maximum_filename_long = 0x40;
  uint16_t filename_long = maximum_filename_long;
  char filename[MAXIMUM_FILENAME_LONG] = "";
  uint16_t gross_filename_long = maximum_filename_long;
  char gross_filename[MAXIMUM_FILENAME_LONG] = "";
  uint16_t file_sort = 0;
  uint16_t gross_text_long = 0;
  const char *input_filename = argv[1];
  char recipe_text[MAXIMUM_PAPER_LONG] = "";
  uint16_t recipe_text_magnitude = MAXIMUM_PAPER_LONG;
  // load text from file
  // const char *recipe_text =
  //    "kratta krathnimna li hcantlattyehka hsactu zrondofi fe";
  // const uint16_t recipe_text_magnitude = (uint16_t)strlen(recipe_text);
  uint16_t recipe_magnitude = 5;
  paper_read(input_filename, 0, &recipe_text_magnitude, recipe_text);
  printf("%s:%d\tinput file:\n%s", __FILE__, __LINE__, recipe_text);
  v16us recipe[8] = {0};
  uint16_t text_remainder = 0;
  uint8_t tablet_indexFinger = 0;
  uint16_t recipe_byte_magnitude =
      (uint16_t)(recipe_magnitude * TABLET_LONG * WORD_THICK);
  memset(recipe, 0, (size_t)(recipe_byte_magnitude));
  // printf(" te1 \n");
  // convert text to binary encoding
  assert(text_remainder == 0);
  // printf(" te2 \n");
  text_encoding(recipe_text_magnitude, recipe_text, &recipe_magnitude, recipe,
                &text_remainder);
  // printf(" yep recipe_magnitude 0x%X \n", recipe_magnitude);
  // convert binary to OpenCL source code
  // print binary

  uint16_t recipe_indexFinger = 0;
  for (recipe_indexFinger = 0; recipe_indexFinger < recipe_magnitude;
       ++recipe_indexFinger) {
    printf("\n%s:%d\trecipe[%X]", __FILE__, __LINE__, recipe_indexFinger);
    for (tablet_indexFinger = 0; tablet_indexFinger < (TABLET_LONG);
         ++tablet_indexFinger) {
      if (tablet_indexFinger % 0x10 == 0)
        printf("\n");
      printf("%04X ",
             (uint)v16us_read(tablet_indexFinger, recipe[recipe_indexFinger]));
    }
  }
  printf("\n");

  // printf(" yep2 recipe_magnitude 0x%X \n", recipe_magnitude);
  // printf("recipe_magnitude 0x%X\n", recipe_magnitude);
  for (recipe_indexFinger = 0; recipe_indexFinger < recipe_magnitude;
       ++recipe_indexFinger) {
    // printf("produce_text %s gross_text_long 0x%X\n", produce_text,
    //       gross_text_long);
    assert(gross_text_long < MAXIMUM_PRODUCE_TEXT_LONG);
    code_opencl_translate(1, &(recipe[recipe_indexFinger]), &produce_text_long,
                          produce_text + gross_text_long, &filename_long,
                          filename, &file_sort);
    // text_file_addenda(produce_text_long, produce_text, gross_filename);
    gross_text_long += produce_text_long;
    produce_text_long = MAXIMUM_PRODUCE_TEXT_LONG - gross_text_long;
    // printf("recipe %X produce text '%s' produce_text_long %X\n",
    //      recipe_indexFinger, produce_text, produce_text_long);
  }

  printf("filename %X %s\n", filename_long, filename);
  derive_filename(filename_long, filename, file_sort, &produce_text_long,
                  gross_filename);
  printf("gross_filename %X %s\n", gross_filename_long, gross_filename);
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
  printf("%s:%d\ttext_long:\t0x%X\n\ttext:\t`%s'\n\t"
         "filename_long:\t0x%X\n\tfilename:\t`%s'\n\tfile_sort:\t%X\n\t"
         "gross_filename:\t`%s'\n",
         __FILE__, __LINE__, produce_text_long, produce_text, filename_long,
         filename, file_sort, gross_filename);
  derive_filename(filename_long, filename, file_sort, &gross_filename_long,
                  gross_filename);
  text_file_addenda(gross_text_long, produce_text, gross_filename);
  printf("TODO break up seed.c into multiple files, encoding, decoding,"
         " compiling\n");
  probe();
  return 0;
}
