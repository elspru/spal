/*SPEL encoding program
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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericOpenCL.h"
#include "seed.h"
#define NEWSPAPER_LONG 0x10
#define MAX_SOURCE_SIZE (0x100000)
uint8_t newspaper_indexFinger = 0;
const uint16_t newspaper_byte_size = NEWSPAPER_LONG * TABLET_BYTE_LONG;
// v16us newspaper[NEWSPAPER_LONG] = {0};

/**
 * \brief Basic integer array addition implemented in OpenCL.
 * \details A sample which shows how to add two integer arrays and store the
 * result in a third array.
 *          The main calculation code is in an OpenCL kernel which is executed
 * on a GPU device.
 * \return The exit code of the application, non-zero if a problem occurred.
 */

int main(int argument_long, char *argument_list[]) {
  if (argument_long < 2) {
    fprintf(stderr, "encoding required text argument error\n");
    return 1;
  }
  uint16_t tablet_indexFinger = 0;
  char *text = argument_list[1];
  uint16_t text_long = (uint16_t)strlen(text);
  uint16_t tablet_long = 1;
  v16us tablet[1] = {0};
  uint16_t text_remains = 0;
  printf("%s\n", text);
  text_encoding(text_long, text, &tablet_long, tablet, &text_remains);
  printf("{\n");
  for (tablet_indexFinger = 0; tablet_indexFinger < (tablet_long * TABLET_LONG);
       ++tablet_indexFinger) {
    if (tablet_indexFinger % 0x10 == 0) {
      printf("{");
    }
    if (tablet_indexFinger != 0 && tablet_indexFinger % 0xF == 0) {
      printf("0x%X}\n", (uint)((uint16_t *)tablet)[tablet_indexFinger]);
    } else {
      printf("0x%X, ", (uint)((uint16_t *)tablet)[tablet_indexFinger]);
    }
  }
  printf("}\n");
}
