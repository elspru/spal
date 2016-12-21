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

#include <CL/cl_platform.h>
#include <CL/cl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericOpenCL.h"
#include "seed.h"
#define NEWSPAPER_LONG 0x10
uint8_t newspaper_indexFinger = 0;
const uint16_t newspaper_byte_magnitude = NEWSPAPER_LONG * TABLET_BYTE_LONG;
// v16us newspaper[NEWSPAPER_LONG] = {0};

int main(void) {
  // Generic Algorithm:
  // load text from file
  // convert text to binary encoding
  // convert binary to OpenCL source code


  // load text from file
  const char *recipe_text =
      "kratswicta kratswichnimna li zrundofi fe";
  const uint16_t recipe_text_magnitude =
      (uint16_t)strlen(recipe_text);
  uint16_t recipe_magnitude = 4;
  v16us recipe[8];
  uint16_t text_remainder = 0;
  uint8_t tablet_indexFinger = 0;
  uint16_t recipe_byte_magnitude =
      (uint16_t)(recipe_magnitude * TABLET_LONG * WORD_THICK);
  memset(recipe, 0,
         (size_t)(recipe_byte_magnitude));
  printf(" te1 \n");
  // convert text to binary encoding
  assert(text_remainder == 0);
  printf(" te2 \n");
  text_encoding(recipe_text_magnitude,
                recipe_text,
                &recipe_magnitude, recipe,
                &text_remainder);
  printf(" yep \n");
  // convert binary to OpenCL source code
    // print binary
  for (tablet_indexFinger = 0;
       tablet_indexFinger < (recipe_magnitude * TABLET_LONG);
       ++tablet_indexFinger) {
    if (tablet_indexFinger % 0x10 == 0)
      printf("\n");
    printf("%04X ", (uint)((uint16_t *)recipe)[tablet_indexFinger]);
  }
  printf("\n");

  v4us code_name = {0};
  derive_code_name((uint8_t) recipe_magnitude, recipe, &code_name);
  printf("code_name %02X \n", ((uint16_t )code_name.s0));
  printf("code_name %08X \n", *((uint32_t *)&code_name));
  printf("code_name %016lX \n", *((uint64_t *)&code_name));
  
  return 0;
}
