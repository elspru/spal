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
// language text file be output

// parallel algorithm begin
//  output buffer evenly spaced, 32 bytes (maximum foreign word length) times
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
//    if same then put translation into output buffer
// language unique allotment _nom done _rea
//
//  after complete run a script to transform output buffer into plain text.
//  write to file or stdout
//
//

// translation dictionary and code file be input
// language text file be output

// parallel algorithm begin
//  output buffer evenly spaced, 32 bytes (maximum foreign word length) times
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
//    if same then put translation into output buffer
// language unique allotment _nom done _rea
//
//  after complete run a script to transform output buffer into plain text.
//  write to file or stdout
//
//
////////////////////////////////////////////
///  code

// translation dictionary and code file be input
// language text file be output
//

// parallel algorithm begin
void code_file_translation(const uint32_t dictionary_long, const char * dictionary, 
      const uint32_t code_long, v16us * code,
      uint32_t produce_pad_long, char * produce_pad) {   
//  output buffer evenly spaced, maximum foreign word length (30 bytes)  times
//  vector long (16), times number of vectors.
//  use maximum that will fit in cache 
  assert(produce_pad_long >= MAXIMUM_FOREIGN_WORD_LONG*TABLET_LONG*code_long);
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
//    if same then put translation into output buffer
// language unique allotment _nom done _rea
//
}

int main(int argument_count, const char * argument_series[]){
// get input args
  if (argument_count < 2) {
    printf("no dictionary filename\n");
    return 0;
  } else if (argument_count < 3) {
    printf("no code filename\n");
  }
  const char *dictionary_filename = argument_series[1];
  const char *code_filename = argument_series[2];
// find 
//  output buffer evenly spaced, 32 bytes (maximum foreign word length) times
//  vector long (16), times number of vectors.
//  use maximum that will fit in cache 
//  after complete run a script to transform output buffer into plain text.
//  write to file or stdout
}
