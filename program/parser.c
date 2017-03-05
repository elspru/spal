#include "sort.h"
#include "parser.h"

#include <assert.h>


const uint8_t consonant_one_code_group[CONSONANT_ONE_ENCODE_LONG][2] =
    {/* LOC 0 ESS consonant one */
     {(uint8_t)'S', 0x0},  {(uint8_t)'m', 0x1},  {(uint8_t)'k', 0x2},
     {(uint8_t)'y', 0x3},  {(uint8_t)'p', 0x4},  {(uint8_t)'w', 0x5},
     {(uint8_t)'n', 0x6},  {(uint8_t)'L', 0x7},  {(uint8_t)'S', 0x8},
     {(uint8_t)'s', 0x9},  {(uint8_t)'t', 0xA},  {(uint8_t)'l', 0xB},
     {(uint8_t)'f', 0xC},  {(uint8_t)'c', 0xD},  {(uint8_t)'r', 0xE},
     {(uint8_t)'L', 0xF},  {(uint8_t)'S', 0x10}, {(uint8_t)'b', 0x11},
     {(uint8_t)'g', 0x12}, {(uint8_t)'d', 0x13}, {(uint8_t)'z', 0x14},
     {(uint8_t)'j', 0x15}, {(uint8_t)'v', 0x16}, {(uint8_t)'L', 0x17},
     {(uint8_t)'S', 0x18}, {(uint8_t)'q', 0x19}, {(uint8_t)'x', 0x1A},
     {(uint8_t)'4', 0x1B}, {(uint8_t)'8', 0x1C}, {(uint8_t)'Q', 0x1D},
     {(uint8_t)'S', 0x1E}, {(uint8_t)'L', 0x1F}};
const uint8_t consonant_one_vocal_group[CONSONANT_ONE_VOCAL_LONG][2] = {
    {(uint8_t)'b', 0x11}, {(uint8_t)'g', 0x12}, {(uint8_t)'d', 0x13}};
const uint8_t consonant_two_code_group[CONSONANT_TWO_ENCODE_LONG][2] = {
    /* LOC 1 ESS consonant two */
    {(uint8_t)'y', 0}, {(uint8_t)'w', 1}, {(uint8_t)'s', 2}, {(uint8_t)'z', 2},
    {(uint8_t)'l', 3}, {(uint8_t)'f', 4}, {(uint8_t)'v', 4}, {(uint8_t)'c', 5},
    {(uint8_t)'j', 5}, {(uint8_t)'r', 6}, {(uint8_t)'x', 7}};
const uint8_t consonant_two_vocal_group[CONSONANT_TWO_VOCAL_LONG][2] = {
    /* LOC 1 ESS consonant two */
    {(uint8_t)'y', 0}, {(uint8_t)'w', 1}, {(uint8_t)'z', 2}, {(uint8_t)'l', 3},
    {(uint8_t)'v', 4}, {(uint8_t)'j', 5}, {(uint8_t)'r', 6}, {(uint8_t)'x', 7}};
const uint8_t consonant_two_aspirate_group[CONSONANT_TWO_ASPIRATE_LONG][2] = {
    /* LOC 1 ESS consonant two */
    {(uint8_t)'y', 0}, {(uint8_t)'w', 1}, {(uint8_t)'s', 2}, {(uint8_t)'l', 3},
    {(uint8_t)'f', 4}, {(uint8_t)'c', 5}, {(uint8_t)'r', 6}, {(uint8_t)'x', 7}};
const uint8_t vowel_code_group[VOWEL_ENCODE_LONG][2] = {
    /* LOC 2 ESS vowel */
    {(uint8_t)'i', 0}, {(uint8_t)'a', 1}, {(uint8_t)'u', 2}, {(uint8_t)'e', 3},
    {(uint8_t)'o', 4}, {(uint8_t)'6', 5}, {(uint8_t)'1', 6}, {(uint8_t)'3', 7}};
const uint8_t tone_code_group[TONE_ENCODE_LONG][2] = {
    /* LOC 3 ESS tone */
    {(uint8_t)'E', 0},
    {(uint8_t)'M', 1},
    {(uint8_t)'7', 2},
    {(uint8_t)'_', 3}};
const uint8_t consonant_three_code_group[CONSONANT_THREE_ENCODE_LONG][2] = {
    /* LOC 4 ESS consonant three */
    {(uint8_t)'m', 0}, {(uint8_t)'k', 1}, {(uint8_t)'p', 2}, {(uint8_t)'n', 3},
    {(uint8_t)'s', 4}, {(uint8_t)'t', 5}, {(uint8_t)'f', 6}, {(uint8_t)'c', 7}};
// const char secondary_group[] = {'f','s','c','y',
//    'r','w','l','x', 'z','j','v'};
//#define SECONDARY_SET_LONG 11
// const char last_group[] = {'p','t','k','f', 's','c','n','m'};
//#define LAST_SET_LONG 8

const char consonant_group[] = {'p', 't', 'k', 'f', 's', 'c', 'x', 'b',
                                'd', 'g', 'v', 'z', 'j', 'n', 'm', 'q',
                                'r', 'l', 'y', 'w', '1', '8', 'h', '.'};
const uint8_t consonant_group_magnitude = 23;
const char vowel_group[] = {'i', 'a', 'u', 'e', 'o', '6'};
const uint8_t vowel_group_magnitude = 6;
const char tone_group[] = {'M', '7', '_'};
const uint8_t tone_group_magnitude = 3;

extern inline uint8_t vowel_Q(const char glyph) {
  uint8_t i;
  for (i = 0; i < vowel_group_magnitude; i++) {
    if (vowel_group[i] == glyph) {
      return TRUE;
    }
  }
  return FALSE;
}
extern inline uint8_t tone_Q(const char glyph) {
  uint8_t i;
  for (i = 0; i < tone_group_magnitude; i++) {
    if (tone_group[i] == glyph) {
      return TRUE;
    }
  }
  return FALSE;
}
 uint8_t consonant_Q(const char glyph) {
  uint8_t i;
  for (i = 0; i < consonant_group_magnitude; ++i) {
    if (consonant_group[i] == glyph) {
      return TRUE;
    }
  }
  return FALSE;
}

int isspace(char letter) {
  if (letter <= 0x20) {
    return 0 == 0;
  } else {
    return 0 == 1;
  }
}

#define first_word_derive_exit                                                 \
  *word_long = (uint8_t)0;                                                     \
  return;


void first_word_derive(const uint16_t text_long, const char *ACC_text,
                       uint8_t *word_long, uint16_t *word_begin) {
  uint8_t start = 0;
  assert(ACC_text != NULL);
  assert(text_long > 1);
  assert(word_begin != NULL);
  /* algorithm:
      if glyph zero ESS vowel
      then if glyph two not ESS consonant
          then answer ACC DEP wrong ACC glyph LOC two
          else restart ABL glyph two
      if glyph zero ESS consonant
      then
          if glyph one ESS consonant CNJ glyph two ESS vowel
              CNJ glyph three ESS consonant
          then copy ACC text ABL glyph zero ALLA glyph
                  four DAT word
              CNJ copy ACC number four DAT size
              answer
          else if glyph one ESS vowel
          then copy ACC text ABL glyph zero ALLA glyph two
              DAT word CNJ
              copy ACC number two DAT size
  */
  for (; start < text_long; ++start) { // skips initial white space
    if (!isspace(*(ACC_text + start)))
      break;
  }
  assert(vowel_Q(ACC_text[start + 0]) == TRUE ||
         consonant_Q(ACC_text[start + 0]) == TRUE);
  if (vowel_Q(ACC_text[start]) == TRUE) {
    if (consonant_Q(ACC_text[start + 1]) == FALSE ||
        consonant_Q(ACC_text[start + 2]) == FALSE) {
      first_word_derive_exit;
    }
    assert(consonant_Q(ACC_text[start + 1]) == TRUE);
    assert(consonant_Q(ACC_text[start + 2]) == TRUE);
    start = 2;
  }
  if (consonant_Q(ACC_text[start]) == TRUE) {
    if (consonant_Q(ACC_text[start + 1]) == TRUE) {
      if (vowel_Q(ACC_text[start + 2]) == FALSE) {
        first_word_derive_exit;
      }
      assert(vowel_Q(ACC_text[start + 2]) == TRUE);
      if (tone_Q(ACC_text[start + 3]) == TRUE) {
        if (consonant_Q(ACC_text[start + 4]) == FALSE) {
          first_word_derive_exit;
        }
        assert(consonant_Q(ACC_text[start + 4]) == TRUE);
        *word_begin = start;
        *word_long = (uint8_t)5;
        return;
      } else {
        if (consonant_Q(ACC_text[start + 3]) == FALSE) {
          first_word_derive_exit;
        }
        assert(consonant_Q(ACC_text[start + 3]) == TRUE);
        *word_begin = start;
        *word_long = (uint8_t)4;
      }
    } else if (vowel_Q(ACC_text[start + 1]) == TRUE) {
      if (tone_Q(ACC_text[start + 2]) == TRUE) {
        *word_begin = start;
        *word_long = (uint8_t)3;
      } else {
        *word_begin = start;
        *word_long = (uint8_t)2;
      }
    }
  }
  if (text_long < *word_long) {
    *word_long = 0;
  }
}
