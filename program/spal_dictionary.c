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
#include "parser.h"
#include "seed.h"
#define VALGRIND
#define NEWLINE '\n'
#define HOLLOW_LETTER ' '

static void paper_addenda(const char *file_name, const uint16_t paper_size,
                          const char *paper_storage) {
  FILE *file_spot = NULL;
  int answer = 0;
  uint16_t size = 0;
  assert(file_name != 0);
  assert(strlen(file_name) > 0);
  assert(paper_storage != NULL);
  file_spot = fopen(file_name, "a");
  assert(file_spot != NULL);
  if (file_spot != NULL) {
    // assert(answer == 0);
    if (answer == 0) {
      size = (uint16_t)(fwrite(paper_storage, 1, paper_size, file_spot));
      if (size != paper_size) {
        printf("write to file failed, paper_size %X size %X", paper_size, size);
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
  const char *word_constant = "_WORD";
  const char *grammar_word_constant = "_GRAMMAR";
  for (line_indexFinger = 0; line_indexFinger < line_long; ++line_indexFinger) {
    if (line_text[line_indexFinger] == HOLLOW_LETTER) {
      break;
    }
  }
  // printf("%.*s \n", line_long, line_text);
  assert(line_indexFinger < line_long);
  word_long = line_indexFinger;
  assert(word_long < WORD_LONG + 1);
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
  // if pyash word ends in h, or is less than 4 long, then GRAMWORD
  if (line_text[word_long - 1] == 'h' || word_long < 4) {
    *define_list_deviation += sprintf(
        define_list_text + *define_list_deviation, "%s 0x%04X // %.*s\n",
        grammar_word_constant, pyash_code, word_long, line_text);
  } else {
    *define_list_deviation += sprintf(define_list_text + *define_list_deviation,
                                      "%s 0x%04X // %.*s\n", word_constant,
                                      pyash_code, word_long, line_text);
  }
  // printf("dll %X dld %X %.*s \n", define_list_long, *define_list_deviation,
  //       line_long, line_text);
  //--*define_list_deviation;// -= 2; // take off the null
  assert(define_list_long > *define_list_deviation);
}

void define_list_establish(const uint16_t paper_long, const char *paper_text,
                           uint16_t *define_list_long, char *define_list_text,
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
                            *define_list_long, define_list_text,
                            &define_list_deviation);
      // printf("DLT `%.*s'", indexFinger - line_begin_indexFinger,
      //       paper_text + line_begin_indexFinger);
      line_begin_indexFinger = indexFinger + 1;
      // printf("DLT `%.*s'", 10, paper_text + line_begin_indexFinger);
    }
  }
  *define_list_long = define_list_deviation;
  *remains = paper_long - line_begin_indexFinger;
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no input filename\n");
    return 0;
  } else if (argc < 3) {
    printf("no produce filename\n");
  }
  const char *filename = argv[1];
  const char *produce_filename = argv[2];
  char paper_text[MAXIMUM_PAPER_LONG * 2] = "";
  char produce_paper_text[MAXIMUM_PAPER_LONG * 3] = "";
  // read word list, for each generate the code
  // read dictionary, line format "pyash_word foreign_word"
  uint paper_indexFinger = 0;
  const uint16_t maximum_paper_long = MAXIMUM_PAPER_LONG * 2;
  uint16_t paper_long = maximum_paper_long;
  const uint16_t maximum_produce_paper_long = MAXIMUM_PAPER_LONG * 3;
  uint16_t produce_paper_long = maximum_produce_paper_long;
  uint16_t paper_remains = 0;
  uint16_t paper_deviation = 0;
  const char *introductory_text = "#ifndef PYASH_H\n#define PYASH_H\n";
  const uint16_t introductory_text_long = (uint16_t)strlen(introductory_text);
  const char *finally_text = "#endif\n";
  const uint16_t finally_text_long = (uint16_t)strlen(finally_text);
  char dictionary_file[DICTIONARY_DATABASE_LONG] = {0};
  uint32_t dictionary_file_long = 0;
  remove(produce_filename);

  paper_addenda(produce_filename, introductory_text_long, introductory_text);
  for (paper_indexFinger = 0;
       paper_indexFinger < MAXIMUM_PAPER_MAGNITUDE && paper_long != 0;
       ++paper_indexFinger) {
    paper_long = maximum_paper_long - paper_deviation;
    paper_read(filename, paper_indexFinger, &paper_long,
               paper_text + paper_deviation);
    memcpy(dictionary_file + dictionary_file_long, paper_text + paper_deviation,
           paper_long);
    dictionary_file_long += paper_long;
    // printf("%s\n", paper_text);
    // printf("`%.*s' paper_long 0x%X paper_number 0x%X\n", paper_deviation +
    // 10,
    //  paper_text, paper_long, paper_indexFinger);
    // process paper_text into produce_paper and mention text remains
    define_list_establish(paper_long + paper_deviation, paper_text,
                          &produce_paper_long, produce_paper_text,
                          &paper_remains);
    // printf("PPT %.*s paper_remains %X \n", paper_remains,
    //       paper_text + ((paper_long + paper_deviation) - paper_remains),
    //       paper_remains);
    // append produce_text to output file
    // paper_write(produce_filename, paper_number,
    //                    uint16_t paper_size, char *paper_storage)
    paper_addenda(produce_filename, produce_paper_long, produce_paper_text);

    // clear paper and set paper long accordingly
    // printf("pl %X ppt %.*s \n", paper_long, paper_remains,
    //       paper_text + (paper_long - (paper_remains)));
    // paper_remains;
    memcpy(paper_text,
           paper_text + (paper_long + paper_deviation - paper_remains),
           paper_remains);
    paper_deviation = paper_remains;
    memset(paper_text + paper_remains, 0,
           (paper_long + paper_deviation) - paper_deviation);
    paper_remains = 0;
    memset(produce_paper_text, 0, maximum_produce_paper_long);
    produce_paper_long = maximum_produce_paper_long;
  }
  paper_addenda(produce_filename, finally_text_long, finally_text);
  //
  // translation file:
  // for each line derive code for pyash_word, and addenda foreign_word in
  // 30byte
  // area after it.
  char dictionary_database[DICTIONARY_DATABASE_LONG] = {0};
  uint32_t dictionary_long = 0;
  uint32_t line_begin = 0;
  uint32_t line_long = 0;
  uint32_t dictionary_file_indexFinger = 0;
  uint8_t word_long = 0;
  uint16_t word_begin = 0;
  uint16_t word_code = 0;
  uint32_t foreign_word_begin = 0;
  uint16_t foreign_word_long = 0;
  //    go through file one line at a time
  // printf("%s:%d dictionary_file %s\n", __FILE__, __LINE__,dictionary_file);
  for (; dictionary_file_indexFinger < dictionary_file_long;
       ++dictionary_file_indexFinger) {
    if (dictionary_file[dictionary_file_indexFinger] == '\n') {
      // printf("%s:%d dictionary_long 0x%X\n", __FILE__,
      // __LINE__,dictionary_long);
      line_long = dictionary_file_indexFinger - line_begin;
      // get the word to encode
      first_word_derive(WORD_LONG, dictionary_file + line_begin, &word_long,
                        &word_begin);
      // encode the word
      // printf("%s:%d word_long 0x%X\n", __FILE__, __LINE__, word_long);
      if (word_long == 0) {
        break;
      }
      word_number_encode(word_long, dictionary_file + line_begin + word_begin,
                         &word_code);
      // get the foreign word
      foreign_word_begin = line_begin + word_begin + word_long + TAB_SIZE;
      foreign_word_long =
          (uint16_t)(dictionary_file_indexFinger - foreign_word_begin);
      assert(foreign_word_long < MAXIMUM_FOREIGN_WORD_LONG);
      // addenda the word code
      memcpy(dictionary_database + dictionary_long, &word_code, CODE_LONG);
      dictionary_long += CODE_LONG;
      // addenda the foreign word
      memcpy(dictionary_database + dictionary_long,
             dictionary_file + foreign_word_begin, foreign_word_long);
      dictionary_long += foreign_word_long;
      // addenda any extra spaces
      memset(dictionary_database + dictionary_long, SPACE_LETTER,
             MAXIMUM_FOREIGN_WORD_LONG - foreign_word_long);
      dictionary_long += MAXIMUM_FOREIGN_WORD_LONG - foreign_word_long;
      dictionary_database[dictionary_long - 1] = '\n';
      assert(dictionary_long <= DICTIONARY_DATABASE_LONG);
      line_begin = dictionary_file_indexFinger;
    }
  }
  // dictionary_database[dictionary_long-1] = (char) 0;

  // append to file after each system page of output
  //
  // uint16_t paper_magnitude = (uint16_t)(
  // dictionary_long/MAXIMUM_PAPER_MAGNITUDE);
  //   paper_long = MAXIMUM_PAPER_MAGNITUDE;
  // for (paper_indexFinger = 0;
  //     paper_indexFinger <= paper_magnitude;
  //     ++paper_indexFinger) {
  //   if(dictionary_long < MAXIMUM_PAPER_MAGNITUDE ) {
  //     paper_long = (uint16_t) dictionary_long;
  //   }
  // printf("%s:%d dictionary_long 0x%X\n", __FILE__, __LINE__,dictionary_long);
  produce_filename = "probe/en.kwon";
  remove(produce_filename);
  printf("%s:%d writing dictionary database '%s'\n", __FILE__, __LINE__,
         produce_filename);
  text_file_addenda(dictionary_long, dictionary_database, produce_filename);
  //   dictionary_long -= paper_long;
  // }

  //
  // define file:
  // for each line generate code for pyash_word, and make corresponding line of
  // the form:
  // sprintf("define %s 0x%04X\n", foreign_word, pyash_word)
  return 0;
}
