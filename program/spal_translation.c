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
#include "dialogue.h"
#include "seed.h"
#include <assert.h>

// translation dictionary and code file be input
// language text file be produce

// parallel algorithm begin
//  produce buffer evenly spaced, 32 bytes (maximum foreign word length) times
//  vector long (16), times number of vectors.
//  use maximum that will fit in cache
//
// language unique allotment _nom begin _rea
//    each worker _nom single independentClause _acc processing _rea
//      number of code words to be translated counter
//      index of applicable words, quoted treated aside.
//    each translation dictionary code _nom each code word _acc comparison _rea
//      after each successful translation decrement code words to be translated
//        counter.
//    if code word remains counter equals zero then skip to next word if
//    available.
//    if same then put translation into produce buffer
// language unique allotment _nom done _rea
//
//  after complete run a script to transform produce buffer into plain text.
//  write to file or stdout
//
//

// translation dictionary and code file be input
// language text file be produce

// parallel algorithm begin
//  produce buffer evenly spaced, 32 bytes (maximum foreign word length) times
//  vector long (16), times number of vectors.
//  use maximum that will fit in cache
//
// language unique allotment _nom begin _rea
//    each worker _nom single independentClause _acc processing _rea
//      number of code words to be translated counter
//      index of applicable words, quoted treated aside.
//    each translation dictionary code _nom each code word _acc comparison _rea
//      after each successful translation decrement code words to be translated
//        counter.
//    if code word remains counter equals zero then skip to next word if
//    available.
//    if same then put translation into produce buffer
// language unique allotment _nom done _rea
//
//  after complete run a script to transform produce buffer into plain text.
//  write to file or stdout
//
//
////////////////////////////////////////////
///  code

// translation dictionary and code file be input
// language text file be produce
//

// parallel algorithm begin
void code_file_translation(const uint32_t dictionary_long,
                           const char *dictionary, const uint32_t code_long,
                           v16us *code, uint32_t *produce_pad_long,
                           char *produce_pad) {
  //  produce buffer evenly spaced, maximum foreign word length (30 bytes) times
  //  vector long (16), times number of vectors.
  //  use maximum that will fit in cache
  assert(produce_pad_long != NULL);
  assert(*produce_pad_long >=
         MAXIMUM_FOREIGN_WORD_LONG * TABLET_LONG * code_long);
  assert(dictionary_long > 0);
  assert(dictionary != NULL);
  assert(code_long > 0);
  assert(code != NULL);
  assert(produce_pad != NULL);
  //
  // language unique allotment _nom begin _rea
  //    each worker _nom single independentClause _acc processing _rea
  //      number of code words to be translated counter
  //      index of applicable words, quoted treated aside.
  //    each translation dictionary code _nom each code word _acc comparison
  //    _rea
  //      after each successful translation decrement code words to be
  //      translated
  //        counter.
  //    if code word remains counter equals zero then skip to next word if
  //    available.
  //    if same then put translation into produce buffer
  // language unique allotment _nom done _rea
  //
}

void pad_text_adaptation(const uint32_t produce_pad_long,
                         const char *produce_pad, uint32_t *produce_text_long,
                         char *produce_text) {
  assert(produce_pad_long > 0);
  assert(produce_pad != NULL);
  assert(produce_text_long != NULL);
  assert(produce_text != NULL);
  assert(*produce_text_long >= produce_pad_long);
  uint32_t pad_indexFinger = 0;
  const uint32_t max_produce_text_long = *produce_text_long;
  uint32_t produce_indexFinger = 0;
  char stream_letter = (char)0;
  for (; pad_indexFinger < produce_pad_long; ++pad_indexFinger) {
    stream_letter = produce_pad[pad_indexFinger];
    if (stream_letter != 0) {
      produce_text[produce_indexFinger] = stream_letter;
      ++produce_indexFinger;
    }
  }
  assert(produce_indexFinger < max_produce_text_long);
  produce_text[produce_indexFinger] = (char)0;
  *produce_text_long = produce_indexFinger;
}

void gross_code_line_v16us_code_translation(const uint32_t gross_code_long,
                                            const char *gross_code,
                                            v16us *code) {
  assert(gross_code_long >= TABLET_BYTE_LONG);
  assert(code != NULL);
  uint16_t code_word = 0;
  uint8_t code_indexFinger = 0;
  for (; code_indexFinger < TABLET_LONG; ++code_indexFinger) {
    code_word = (uint16_t)(gross_code[code_indexFinger * 2] |
                           gross_code[code_indexFinger * 2 + 1] << 0x8);
    v16us_write(code_indexFinger, code_word, code);
  }
}
void gross_code_v16us_code_translation(const uint32_t gross_code_long,
                                       const char *gross_code,
                                       uint16_t *code_long, v16us *code) {
  // translate each line
  assert(gross_code_long > 0);
  assert(gross_code_long % TABLET_BYTE_LONG == 0);
  assert(gross_code != NULL);
  assert(code_long != NULL);
  assert(*code_long >= gross_code_long / TABLET_BYTE_LONG);
  assert(code != NULL);
  uint32_t gross_code_indexFinger = 0;
  uint16_t code_indexFinger = 0;
  for (; gross_code_indexFinger < gross_code_long;
       gross_code_indexFinger += TABLET_BYTE_LONG) {
    gross_code_line_v16us_code_translation(
        gross_code_long - gross_code_indexFinger,
        gross_code + gross_code_indexFinger, code + code_indexFinger);
    ++code_indexFinger;
  }
}

int main(int argument_count, const char *argument_series[]) {
  // get input args
  if (argument_count < 2) {
    printf("no dictionary filename\n");
    return 1;
  } else if (argument_count < 3) {
    printf("no code filename\n");
    return 2;
  }
  const char *dictionary_filename = argument_series[1];
  const char *code_filename = argument_series[2];
  // find
  //  produce buffer evenly spaced, 32 bytes (maximum foreign word length) times
  //  tablet long (16), times number of vectors.
  //  use maximum that will fit in cache  (Ryzen cache best under 4MiB, l2 cache
  //  under 512KiB)
  char produce_pad[MAXIMUM_FOREIGN_WORD_LONG * TABLET_LONG * TABLET_PAD_LONG] =
      {0};
  uint32_t produce_pad_long =
      MAXIMUM_FOREIGN_WORD_LONG * TABLET_LONG * TABLET_PAD_LONG;
  //  after complete, run a script to transform produce buffer into plain text.
  char produce_text[MAXIMUM_FOREIGN_WORD_LONG * TABLET_LONG * TABLET_PAD_LONG] =
      {0};
  uint32_t produce_text_long =
      MAXIMUM_FOREIGN_WORD_LONG * TABLET_LONG * TABLET_PAD_LONG;

  // load dictionary from file
  char dictionary[DICTIONARY_DATABASE_LONG] = {0};
  const uint32_t max_dictionary_long = DICTIONARY_DATABASE_LONG;
  uint32_t dictionary_long = max_dictionary_long;
  text_file_read(dictionary_filename, &dictionary_long, dictionary);
  // load code from file into v16us
  char gross_code[TABLET_PAD_LONG * TABLET_BYTE_LONG] = {0};
  const uint32_t max_gross_code_long = TABLET_PAD_LONG * TABLET_BYTE_LONG;
  uint32_t gross_code_long = max_gross_code_long;
  text_file_read(code_filename, &gross_code_long, gross_code);

  printf("%s:%d gross_code_long 0x%X, gross_code:\n %s", __FILE__, __LINE__,
         gross_code_long, gross_code);
  // convert gross code to v16us array
  v16us code[TABLET_PAD_LONG] = {0};
  uint16_t code_long = TABLET_PAD_LONG;
  gross_code_v16us_code_translation(gross_code_long, gross_code, &code_long,
                                    code);

  code_file_translation(dictionary_long, dictionary, code_long, code,
                        &produce_pad_long, produce_pad);

  pad_text_adaptation(produce_pad_long, produce_pad, &produce_text_long,
                      produce_text);
  //  write to file or stdout
}
