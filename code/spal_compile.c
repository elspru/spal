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

#include "genericOpenCL.h"
#include "lookup3.h"
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
  assert(written_text_long == text_long);
  int result = fclose(out);
  assert(result == 0);
}

int main(void) {
  // Generic Algorithm:
  // load text from file
  // convert text to binary encoding
  // convert binary to OpenCL source code

  // load text from file
  const char *recipe_text = "kratta krathnimna li zrundofi fe";
  const uint16_t recipe_text_magnitude = (uint16_t)strlen(recipe_text);
  uint16_t recipe_magnitude = 4;
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
  uint8_t recipe_indexFinger = 0;
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

  uint64_t code_name = 0;
  code_name_derive((uint8_t)recipe_magnitude, recipe, &code_name);
  printf("code_name 64bit %016lX\n", code_name);
  uint16_t produce_text_long = 256;
  char produce_text[256] = "";
  uint16_t filename_long = 64;
  char filename[64] = "";
  uint16_t gross_filename_long = 64;
  char gross_filename[64] = "";
  uint16_t file_sort = 0;
  code_opencl_translate(recipe_magnitude, &(recipe[0]), &produce_text_long,
                        produce_text, &filename_long, filename, &file_sort);
  derive_filename(filename_long, filename, file_sort, &gross_filename_long,
                  gross_filename);
  text_file_addenda(produce_text_long, produce_text, gross_filename);
  code_opencl_translate(recipe_magnitude, &(recipe[1]), &produce_text_long,
                        produce_text, &filename_long, filename, &file_sort);
  // get gross filename based on file sort and filename

  // create file if not existing
  // append to file buffer
  printf("text_long %X text '%s' filename_long %X filename '%s' file_sort %X "
         "gross_filename %s\n",
         produce_text_long, produce_text, filename_long, filename, file_sort,
         gross_filename);

  derive_filename(filename_long, filename, file_sort, &gross_filename_long,
                  gross_filename);
  text_file_addenda(produce_text_long, produce_text, gross_filename);
  return 0;
}

void Test() {}
