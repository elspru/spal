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
#include "genericOpenCL.h"
#include "seed.h"
#define VALGRIND
#define NEWLINE '\n'
#define HOLLOW_LETTER ' '

#define MAXIMUM_PAPER_LONG 4096
#define MAXIMUM_PAPER_MAGNITUDE 4096
static void paper_read(const char *file_name, const size_t paper_number,
                       uint16_t *paper_size, char *paper_storage) {
  FILE *file_spot = NULL;
  int answer = 0;
  uint16_t text_spot = 0;
  uint16_t size = 0;
  int glyph = (char)0;
  assert(file_name != 0);
  assert(strlen(file_name) > 0);
  assert(paper_storage != NULL);
  assert(*paper_size >= MAXIMUM_PAPER_LONG);
  file_spot = fopen(file_name, "r");
  assert(file_spot != NULL);
  if (file_spot != NULL) {
    answer = fseek(file_spot, (int)paper_number * MAXIMUM_PAPER_LONG, SEEK_SET);
    // assert(answer == 0);
    if (answer == 0) {
      size = (uint16_t)(fread(paper_storage, MAXIMUM_PAPER_LONG, 1, file_spot));
      if (size != 0) {
        size = (uint16_t)(size * MAXIMUM_PAPER_LONG);
      } else {
        answer =
            fseek(file_spot, (int)paper_number * MAXIMUM_PAPER_LONG, SEEK_SET);
        assert(answer == 0);
        for (text_spot = 0; text_spot < MAXIMUM_PAPER_LONG; ++text_spot) {
          glyph = fgetc(file_spot);
          if (glyph == EOF)
            break;
          paper_storage[text_spot] = (char)glyph;
          ++size;
        }
      }
      // printf("%X size \n", (uint) size);
    } else {
      printf("fseek fail PFV");
      size = 0;
    }
    answer = fclose(file_spot);
    assert(answer == 0);
  } else {
    printf("file open fail PFV");
    size = 0;
  }
  *paper_size = size;
  // assert(*paper_size != 0);
}

static void paper_write(const char *file_name, const size_t paper_number,
                        uint16_t paper_size, char *paper_storage) {
  FILE *file_spot = NULL;
  int answer = 0;
  uint16_t size = 0;
  assert(file_name != 0);
  assert(strlen(file_name) > 0);
  assert(paper_storage != NULL);
  assert(paper_size <= MAXIMUM_PAPER_LONG);
  file_spot = fopen(file_name, "w");
  assert(file_spot != NULL);
  if (file_spot != NULL) {
    answer = fseek(file_spot, (int)paper_number * MAXIMUM_PAPER_LONG, SEEK_SET);
    // assert(answer == 0);
    if (answer == 0) {
      size = (uint16_t)(fwrite(paper_storage, paper_size, 1, file_spot));
      if (size != paper_size) {
        printf("write to file failed");
      }

    } else {
      printf("fseek fail PFV");
      size = 0;
    }
    answer = fclose(file_spot);
    assert(answer == 0);
  } else {
    printf("file open fail PFV");
    size = 0;
  }
}

void define_line_establish(const uint16_t line_long, const char *line_text,
                           const uint16_t define_list_long,
                           char *define_list_text,
                           uint16_t *define_list_deviation) {
  // split at first space, before is pyash word, after is other text
  assert(line_text != NULL);
  assert(define_list_text != NULL);
  assert(define_list_deviation != NULL);
  uint16_t word_long = 0;
  uint16_t other_word_text_deviation = 0;
  uint16_t other_word_long = 0;
  uint16_t line_indexFinger = 0;
  uint16_t pyash_code = 0;
  for (line_indexFinger = 0; line_indexFinger < line_long; ++line_indexFinger) {
    if (line_text[line_indexFinger] == HOLLOW_LETTER) {
      break;
    }
  }
  printf("%.*s \n", line_long, line_text);
  assert(line_indexFinger < line_long);
  word_long = line_indexFinger;
  assert(word_long < WORD_LONG +1);
  other_word_text_deviation = line_indexFinger + 1;
  other_word_long = line_long - other_word_text_deviation;
  // get code for pyash_word
  word_number_encode((uint8_t)word_long, line_text, &pyash_code);
  // output "#define %s _WORD 0x%X", other_text, pyash_code);
  memcpy(define_list_text + *define_list_deviation, "#define ", 8);
  *define_list_deviation += 8;
  memcpy(define_list_text + *define_list_deviation,
         line_text + other_word_text_deviation, other_word_long);
  *define_list_deviation += other_word_long;
  *define_list_deviation += sprintf(define_list_text + *define_list_deviation,
                                    "_WORD 0x%04X\n", pyash_code);
  printf("dll %X dld %X %.*s \n", define_list_long, *define_list_deviation,
line_long, line_text);
  //--*define_list_deviation;// -= 2; // take off the null
  assert(define_list_long > *define_list_deviation);
}

void define_list_establish(const uint16_t paper_long, const char *paper_text,
                           const uint16_t define_list_long, char *define_list_text,
                           uint16_t *remains) {
  // loop for new lines
  // each line is processed to single definition
  uint16_t indexFinger = 0;
  uint16_t line_begin_indexFinger = 0;
  uint16_t define_list_deviation = 0;
  for (indexFinger = 0; indexFinger < paper_long; ++indexFinger) {
    if (paper_text[indexFinger] == NEWLINE) {
      define_line_establish(indexFinger - line_begin_indexFinger,
                            paper_text + line_begin_indexFinger,
                            define_list_long,
                            define_list_text, &define_list_deviation);
      //printf("DLT %s", define_list_text);
      line_begin_indexFinger = indexFinger + 1;
    }
  }
  *remains = paper_long - line_begin_indexFinger;
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no input filename\n");
    return 0;
  } else if (argc < 3) {
    printf("no produce filename\n");
  }
  char *filename = argv[1];
  char *produce_filename = argv[2];
  char paper_text[MAXIMUM_PAPER_LONG * 2] = "";
  char produce_paper_text[MAXIMUM_PAPER_LONG * 3] = "";
  // read word list, for each generate the code
  // read dictionary, line format "pyash_word foreign_word"
  uint paper_indexFinger = 0;
  uint16_t paper_long = MAXIMUM_PAPER_LONG *2 ;
  uint16_t produce_paper_long = MAXIMUM_PAPER_LONG * 3;
  uint16_t paper_remains = 0;
  uint16_t paper_deviation = 0;
  for (paper_indexFinger = 0;
       paper_indexFinger < MAXIMUM_PAPER_MAGNITUDE && paper_long != 0;
       ++paper_indexFinger) {
    paper_long = MAXIMUM_PAPER_LONG*2;
    paper_read(filename, paper_indexFinger, &paper_long - paper_deviation, paper_text +
paper_deviation);
    //printf("%s\n", paper_text);
    printf("%.*s paper_long %X\n", paper_deviation, paper_text, paper_long);
    // process paper_text into produce_paper and mention text remains
    define_list_establish(paper_long + paper_deviation, paper_text, produce_paper_long,
                          produce_paper_text, &paper_remains);
    printf("PPT %s paper_remains %X \n", produce_paper_text, paper_remains);
    // append produce_text to output file
    //paper_write(produce_filename, paper_number,
    //                    uint16_t paper_size, char *paper_storage) {
  
    // clear paper and set paper long accordingly
    printf("pl %X ppt %.*s \n", paper_long,  paper_remains,
paper_text+(paper_long-(paper_remains)));
    memcpy(paper_text, paper_text+(paper_long-paper_remains), paper_remains);
    paper_deviation = paper_remains;
    paper_remains = 0;
    memset(paper_text+paper_deviation, 0, MAXIMUM_PAPER_LONG*2 - paper_deviation);
    memset(produce_paper_text, 0, produce_paper_long);
  }
  //
  // translation file:
  // for each line generate code for pyash_word, and put foreign_word in 30byte
  // area after it.
  // append to file after each system page of output
  //
  // define file:
  // for each line generate code for pyash_word, and make corresponding line of
  // the form:
  // sprintf("define %s 0x%04X\n", foreign_word, pyash_word)
  return 0;
}
