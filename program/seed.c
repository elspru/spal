/*SPEL virtual machine
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

#include <assert.h> // NOT opencl compatible
#include <stdio.h>  // NOT opencl compatible
#include <string.h> // NOT opencl compatible// uses memset and memcmp

#include "dictionary.h"
//#include "seed.h"

uint64_t v4us_uint64_translation(const v4us vector) {
  return (uint64_t)(
      ((uint64_t)vector.s0 << (16 * 0)) + ((uint64_t)vector.s1 << (16 * 1)) +
      ((uint64_t)vector.s2 << (16 * 2)) + ((uint64_t)vector.s3 << (16 * 3)));
}

void v16us_write(const uint8_t indexFinger, const uint16_t number,
                 v16us *vector) {
  assert(indexFinger < 16);
  switch (indexFinger) {
  case 0:
    (*vector).s0 = number;
    break;
  case 1:
    (*vector).s1 = number;
    break;
  case 2:
    (*vector).s2 = number;
    break;
  case 3:
    (*vector).s3 = number;
    break;
  case 4:
    (*vector).s4 = number;
    break;
  case 5:
    (*vector).s5 = number;
    break;
  case 6:
    (*vector).s6 = number;
    break;
  case 7:
    (*vector).s7 = number;
    break;
  case 8:
    (*vector).s8 = number;
    break;
  case 9:
    (*vector).s9 = number;
    break;
  case 0xA:
    (*vector).sa = number;
    break;
  case 0xB:
    (*vector).sb = number;
    break;
  case 0xC:
    (*vector).sc = number;
    break;
  case 0xD:
    (*vector).sd = number;
    break;
  case 0xE:
    (*vector).se = number;
    break;
  case 0xF:
    (*vector).sf = number;
    break;
  }
}

void delete_empty_glyph(const uint16_t ACC_GEN_magnitude, const char *text,
                        uint16_t *DAT_magnitude, char *DAT_text) {
  uint16_t i = 0;
  uint16_t j = 0;
  char glyph;
  assert(ACC_GEN_magnitude <= *DAT_magnitude);
  assert(text != NULL);
  assert(DAT_text != NULL);
  assert(text != DAT_text);
  for (i = 0; i < ACC_GEN_magnitude; ++i) {
    glyph = text[i];
    if (consonant_Q(glyph) == TRUE || vowel_Q(glyph) == TRUE ||
        tone_Q(glyph) == TRUE) {
      DAT_text[j] = glyph;
      ++j;
    } else {
    }
  }
  *DAT_magnitude = j;
}

void text_copy(const uint8_t size, const char *ACC_text, char *DAT_text) {
  uint8_t i;
  assert(ACC_text != NULL);
  assert(size > 0);
  assert(DAT_text != NULL);
  for (i = 0; i < size; ++i) {
    DAT_text[i] = ACC_text[i];
  }
}
extern inline void copy_ACC_text_DAT_tablet(const char *text,
                                            const uint8_t text_magnitude,
                                            v16us *tablet,
                                            const uint8_t tablet_offset,
                                            const uint8_t tablet_magnitude) {
  uint8_t text_indexFinger;
  uint8_t tablet_indexFinger = 0;
  assert(tablet_magnitude >= text_magnitude / 2 / TABLET_LONG);
  assert(text != NULL);
  assert(tablet != NULL);
  for (text_indexFinger = 0; text_indexFinger < text_magnitude;
       ++text_indexFinger) {
    if (text_magnitude > text_indexFinger + 1) {
      v16us_write(tablet_indexFinger + tablet_offset,
                  (uint16_t)(text[text_indexFinger] |
                             (text[text_indexFinger + 1] << 8)),
                  tablet);
      ++text_indexFinger;
    } else {
      v16us_write(tablet_indexFinger + tablet_offset,
                  (uint16_t)text[text_indexFinger], tablet);
    }
    // printf("tablet %04X \n", (uint) tablet[0][tablet_indexFinger +
    // tablet_offset]);
    ++tablet_indexFinger;
  }
}

#define derive_first_word_exit                                                 \
  *DAT_GEN_magnitude = (uint8_t)0;                                             \
  return;

inline void derive_first_word(const uint8_t ACC_GEN_magnitude,
                              const char *ACC_independentClause,
                              uint8_t *DAT_GEN_magnitude, char *DAT_word) {
  uint8_t start = 0;
  assert(ACC_independentClause != NULL);
  if (ACC_GEN_magnitude < 2) {
    derive_first_word_exit;
  }
  assert(ACC_GEN_magnitude > 1);
  assert(DAT_word != NULL);
  assert(*DAT_GEN_magnitude >= WORD_LONG);
  /* algorithm:
      if glyph zero ESS vowel
      then if glyph two not ESS consonant
          then answer ACC DEP wrong ACC glyph LOC two
          else restart ABL glyph two
      if glyph zero ESS consonant
      then
          if glyph one ESS consonant CNJ glyph two ESS vowel
              CNJ glyph three ESS consonant
          then copy ACC independentClause ABL glyph zero ALLA glyph
                  four DAT word
              CNJ copy ACC number four DAT size
              answer
          else if glyph one ESS vowel
          then copy ACC independentClause ABL glyph zero ALLA glyph two
              DAT word CNJ
              copy ACC number two DAT size
  */
  assert(vowel_Q(ACC_independentClause[start + 0]) == TRUE ||
         consonant_Q(ACC_independentClause[start + 0]) == TRUE);
  if (vowel_Q(ACC_independentClause[start]) == TRUE) {
    if (consonant_Q(ACC_independentClause[start + 1]) == FALSE ||
        consonant_Q(ACC_independentClause[start + 2]) == FALSE) {
      derive_first_word_exit;
    }
    assert(consonant_Q(ACC_independentClause[start + 1]) == TRUE);
    assert(consonant_Q(ACC_independentClause[start + 2]) == TRUE);
    start = 2;
  }
  if (consonant_Q(ACC_independentClause[start]) == TRUE) {
    if (consonant_Q(ACC_independentClause[start + 1]) == TRUE) {
      if (vowel_Q(ACC_independentClause[start + 2]) == FALSE) {
        derive_first_word_exit;
      }
      assert(vowel_Q(ACC_independentClause[start + 2]) == TRUE);
      if (tone_Q(ACC_independentClause[start + 3]) == TRUE) {
        if (consonant_Q(ACC_independentClause[start + 4]) == FALSE) {
          derive_first_word_exit;
        }
        assert(consonant_Q(ACC_independentClause[start + 4]) == TRUE);
        text_copy((uint8_t)(start + 5), ACC_independentClause + start,
                  DAT_word);
        *DAT_GEN_magnitude = (uint8_t)5;
      } else {
        if (consonant_Q(ACC_independentClause[start + 3]) == FALSE) {
          derive_first_word_exit;
        }
        assert(consonant_Q(ACC_independentClause[start + 3]) == TRUE);
        text_copy((uint8_t)(start + 4), ACC_independentClause + start,
                  DAT_word);
        *DAT_GEN_magnitude = (uint8_t)4;
      }
    } else if (vowel_Q(ACC_independentClause[start + 1]) == TRUE) {
      if (tone_Q(ACC_independentClause[start + 2]) == TRUE) {
        text_copy((uint8_t)(start + 3), ACC_independentClause + start,
                  DAT_word);
        *DAT_GEN_magnitude = (uint8_t)3;
      } else {
        text_copy((uint8_t)(start + 2), ACC_independentClause + start,
                  DAT_word);
        *DAT_GEN_magnitude = (uint8_t)2;
      }
    }
  }
  if (ACC_GEN_magnitude < *DAT_GEN_magnitude) {
    *DAT_GEN_magnitude = 0;
  }
}

extern inline void code_ACC_consonant_one(const uint8_t type,
                                          const uint8_t consonant_one,
                                          uint16_t *number) {
  uint8_t i, consonant_number = CONSONANT_ONE_ENCODE_LONG;
  assert(consonant_Q((char)consonant_one) == TRUE);
  if (consonant_one != 0 && type != SHORT_ROOT) {
    for (i = 0; i < CONSONANT_ONE_ENCODE_LONG; i++) {
      if (consonant_one_code_group[i][0] == consonant_one) {
        consonant_number = consonant_one_code_group[i][1];
        assert(consonant_number < CONSONANT_ONE_ENCODE_LONG);
        if (type == LONG_ROOT) {
          *number = consonant_number;
          break;
        } else if (type == LONG_GRAMMAR) {
          *number |= (uint16_t)(consonant_number << BANNER_THICK);
          break;
        } else if (type == SHORT_GRAMMAR) {
          *number |= (uint16_t)(consonant_number << CONSONANT_ONE_THICK);
          break;
        }
      }
    }
  }
  assert(consonant_number != CONSONANT_ONE_ENCODE_LONG);
}

extern inline void code_ACC_consonant_two(const uint8_t type,
                                          const uint8_t consonant_two,
                                          uint16_t *number) {
  uint8_t i, consonant_number = CONSONANT_TWO_ENCODE_LONG;
  uint16_t start_number = *number;
  // printf("n %04X, t %X c2 %c \n", (uint) *number,
  //       (uint) type, (char) consonant_two);
  assert(consonant_Q((char)consonant_two) == TRUE);
  if (consonant_two != 0 && type == SHORT_ROOT) {
    for (i = 0; i < CONSONANT_ONE_ENCODE_LONG; i++) {
      if (consonant_one_code_group[i][0] == consonant_two) {
        consonant_number = consonant_one_code_group[i][1];
        assert(consonant_number < CONSONANT_ONE_ENCODE_LONG);
        *number |= (uint16_t)(consonant_number << BANNER_THICK);
        break;
      }
    }
  }
  if (consonant_two != 0 && type != SHORT_ROOT && type != SHORT_GRAMMAR) {
    for (i = 0; i < CONSONANT_TWO_ENCODE_LONG; i++) {
      if (consonant_two_code_group[i][0] == consonant_two) {
        consonant_number = consonant_two_code_group[i][1];
        assert(consonant_number < CONSONANT_TWO_ENCODE_LONG);
        if (type == LONG_ROOT) {
          // printf("C2LR cn %04X\n", (uint) consonant_number);
          // printf("C2LR %04X\n", (uint) consonant_number <<
          //       (CONSONANT_ONE_THICK));
          *number |= (uint16_t)(consonant_number << CONSONANT_ONE_THICK);
          break;
        } else if (type == LONG_GRAMMAR) {
          *number |= (uint16_t)(consonant_number
                                << (BANNER_THICK + CONSONANT_ONE_THICK));
          break;
        }
      }
    }
  }
  assert(consonant_number == 0 || *number != start_number);
  assert(consonant_number != CONSONANT_ONE_ENCODE_LONG);
}

extern inline void code_ACC_vowel(const uint8_t type, const uint8_t vowel,
                                  uint16_t *number) {
  uint8_t i, vowel_number = VOWEL_ENCODE_LONG;
  // uint16_t start_number = *number;
  // printf("n %04X, t %X v %c \n", (uint) *number,
  //       (uint) type, (char) vowel);
  assert(vowel_Q((char)vowel) == TRUE);
  if (vowel != 0) {
    for (i = 0; i < VOWEL_ENCODE_LONG; i++) {
      if (vowel_code_group[i][0] == vowel) {
        vowel_number = vowel_code_group[i][1];
        assert(vowel_number < VOWEL_ENCODE_LONG);
        if (type == LONG_ROOT) {
          // printf("VLR %04X\n", (uint) vowel_number << (
          //       CONSONANT_ONE_THICK + CONSONANT_TWO_THICK));
          *number |= (uint16_t)(vowel_number
                                << (CONSONANT_ONE_THICK + CONSONANT_TWO_THICK));
          break;
        } else if (type == SHORT_ROOT) {
          *number |=
              (uint16_t)(vowel_number << (BANNER_THICK + CONSONANT_ONE_THICK));
          break;
        } else if (type == LONG_GRAMMAR) {
          // printf("VLG %04X\n", (uint) vowel_number << (BANNER_THICK +
          //       CONSONANT_ONE_THICK + CONSONANT_TWO_THICK));
          *number |=
              (uint16_t)(vowel_number << (BANNER_THICK + CONSONANT_ONE_THICK +
                                          CONSONANT_TWO_THICK));
          break;
        } else if (type == SHORT_GRAMMAR) {
          *number |= (uint16_t)(vowel_number << (CONSONANT_ONE_THICK * 2));
          break;
        }
      }
    }
  }
  // assert(vowel_number == 0 || *number != start_number);
  assert(vowel_number != VOWEL_ENCODE_LONG);
}

extern inline void code_ACC_type(const char *word,
                                 const uint8_t ACC_GEN_magnitude, uint8_t *type,
                                 uint16_t *number) {
  assert(word != NULL);
  assert(ACC_GEN_magnitude <= WORD_LONG);
  // printf("w %s\n", word);
  if (ACC_GEN_magnitude == 2 || ACC_GEN_magnitude == 3) {
    *type = SHORT_GRAMMAR;
    *number = 30;
  } else if (ACC_GEN_magnitude == 4 && word[3] == 'h') {
    *type = LONG_GRAMMAR;
    *number = 7;
  } else if (ACC_GEN_magnitude == 4 && word[0] == 'h') {
    *type = SHORT_ROOT;
    *number = 0;
  } else if (ACC_GEN_magnitude == 4) {
    *type = LONG_ROOT;
    *number = 0;
  } else if (ACC_GEN_magnitude == 5 && word[0] == 'h') {
    *type = SHORT_ROOT;
    *number = 0;
  } else if (ACC_GEN_magnitude == 5 && word[4] == 'h') {
    *type = LONG_GRAMMAR;
    *number = 7;
  } else if (ACC_GEN_magnitude == 5) {
    *type = LONG_ROOT;
    *number = 0;
  } else {
    *type = ERROR_BINARY;
    *number = 0;
  }
  assert(*type != ERROR_BINARY);
}

extern inline void code_ACC_tone(const uint8_t type, const uint8_t tone,
                                 uint16_t *number) {
  uint8_t i, tone_number = TONE_ENCODE_LONG;
  uint16_t start_number = *number;
  // printf("n %04X, t %X tn %c \n", (uint) *number,
  //       (uint) type, (char) tone);
  assert(tone_Q((char)tone) == TRUE);
  if (tone != 0) {
    for (i = 0; i < TONE_ENCODE_LONG; i++) {
      if (tone_code_group[i][0] == tone) {
        tone_number = tone_code_group[i][1];
        if (type == LONG_ROOT) {
          // printf("TLR %X\n", (uint)(tone_number <<
          //       (CONSONANT_ONE_THICK + CONSONANT_TWO_THICK + VOWEL_THICK)));
          *number |=
              (uint16_t)(tone_number << (CONSONANT_ONE_THICK +
                                         CONSONANT_TWO_THICK + VOWEL_THICK));
          break;
        } else if (type == SHORT_ROOT) {
          *number |=
              (uint16_t)(tone_number
                         << (BANNER_THICK + CONSONANT_ONE_THICK + VOWEL_THICK));
          break;
        } else if (type == LONG_GRAMMAR) {
          *number |=
              (uint16_t)(tone_number << (BANNER_THICK + CONSONANT_ONE_THICK +
                                         CONSONANT_TWO_THICK + VOWEL_THICK));
          break;
        } else if (type == SHORT_GRAMMAR) {
          *number |= (uint16_t)(tone_number
                                << (CONSONANT_ONE_THICK * 2 + VOWEL_THICK));
          break;
        }
      }
    }
  }
  assert(tone_number == 0 || *number != start_number);
  assert(tone_number != TONE_ENCODE_LONG);
}

extern inline void code_ACC_consonant_three(const uint8_t type,
                                            const uint8_t consonant_three,
                                            const uint8_t tone,
                                            uint16_t *number) {
  uint8_t i, consonant_number = CONSONANT_THREE_ENCODE_LONG;
  uint16_t start_number = *number;
  // printf("n %04X, t %X c %c  tn %c\n", (uint) *number,
  //       (uint) type, (char) consonant_three, (char) tone);
  if (consonant_three != 0 && type != SHORT_GRAMMAR && type != LONG_GRAMMAR) {
    for (i = 0; i < CONSONANT_THREE_ENCODE_LONG; i++) {
      if (consonant_three_code_group[i][0] == consonant_three) {
        consonant_number = consonant_three_code_group[i][1];
        if (type == LONG_ROOT && tone == 0) {
          // printf("C3LR %04X \n", (uint) (consonant_number
          //               << (CONSONANT_ONE_THICK + CONSONANT_TWO_THICK +
          //                  VOWEL_THICK + TONE_THICK)));
          *number |= (uint16_t)(consonant_number
                                << (CONSONANT_ONE_THICK + CONSONANT_TWO_THICK +
                                    VOWEL_THICK + TONE_THICK));
          break;
        } else if (type == SHORT_ROOT && tone == 0) {
          // printf("SR %04X \n", (uint) (consonant_number
          //               << (BANNER_THICK + CONSONANT_ONE_THICK +
          //               VOWEL_THICK)));
          *number |= (uint16_t)(consonant_number
                                << (BANNER_THICK + CONSONANT_ONE_THICK +
                                    VOWEL_THICK + TONE_THICK));
          break;
        } else if (type == LONG_ROOT && tone != 0) {
          *number |= (uint16_t)(consonant_number
                                << (CONSONANT_ONE_THICK + CONSONANT_TWO_THICK +
                                    VOWEL_THICK + TONE_THICK));
          break;
        } else if (type == SHORT_ROOT && tone != 0) {
          *number |= (uint16_t)(consonant_number
                                << (BANNER_THICK + CONSONANT_ONE_THICK +
                                    VOWEL_THICK + TONE_THICK));
          break;
        }
      }
    }
  }
  assert(consonant_number == 0 || *number != start_number);
  assert(consonant_number != CONSONANT_THREE_ENCODE_LONG);
}
#define code_exit                                                              \
  *DAT_number = 0;                                                             \
  return;
void word_number_encode(const uint8_t ACC_GEN_magnitude, const char *word,
                        uint16_t *DAT_number) {
  /* Algorithm:
      TEL set ACC NUM zero DAT number DEO
      identify type of word
      if ACC word class ESS short root word
      then TEL mark ACC first three binary DAT NUM zero
      else-if ACC word class ESS long grammar word
      then TEL mark ACC first three binary DAT NUM one
      else-if ACC word class ESS short grammar word
      then TEL mark ACC first byte DAT NUM thirty
      UNQ glyph INE indexFinger POSC word QUOT process
      ATEL search ACC code table BEN glyph DAT glyph number DEO
      TEL multiply ACC glyph number INS indexFinger DAT indexFinger number DEO
      TEL add ACC indexFinger number DAT number DEO
      process QUOT DEO
  */
  uint8_t consonant_one = 0, consonant_two = 0, vowel = 0, tone = 0,
          consonant_three = 0, type = LONG_ROOT;
  uint16_t number = 0;
  assert(ACC_GEN_magnitude > 0);
  assert(ACC_GEN_magnitude <= WORD_LONG);
  assert(word != NULL);
  assert(DAT_number != NULL);
  code_ACC_type(word, ACC_GEN_magnitude, &type, &number);
  // printf("type %X\n", (uint) number);
  /* TEL fill ACC glyph variable PL */
  consonant_one = (uint8_t)word[0];
  if (consonant_Q((char)consonant_one) == FALSE) {
    code_exit;
  }
  assert(consonant_Q((char)consonant_one) == TRUE);
  if (ACC_GEN_magnitude == 2) {
    vowel = (uint8_t)word[1];
    if (vowel_Q((char)vowel) == FALSE) {
      code_exit;
    }
    assert(vowel_Q((char)vowel) == TRUE);
  } else if (ACC_GEN_magnitude == 3) {
    vowel = (uint8_t)word[1];
    tone = (uint8_t)word[2];
    if (vowel_Q((char)vowel) == FALSE || tone_Q((char)tone) == FALSE) {
      code_exit;
    }
    assert(vowel_Q((char)vowel) == TRUE);
    assert(tone_Q((char)tone) == TRUE);
  } else if (ACC_GEN_magnitude == 4) {
    consonant_two = (uint8_t)word[1];
    vowel = (uint8_t)word[2];
    consonant_three = (uint8_t)word[3];
    if (consonant_Q((char)consonant_two) == FALSE ||
        vowel_Q((char)vowel) == FALSE ||
        consonant_Q((char)consonant_three) == FALSE) {
      code_exit;
    }
    assert(consonant_Q((char)consonant_two) == TRUE);
    assert(vowel_Q((char)vowel) == TRUE);
    assert(consonant_Q((char)consonant_three) == TRUE);
  } else if (ACC_GEN_magnitude == 5) {
    consonant_two = (uint8_t)word[1];
    vowel = (uint8_t)word[2];
    tone = (uint8_t)word[3];
    consonant_three = (uint8_t)word[4];
    if (consonant_Q((char)consonant_two) == FALSE ||
        vowel_Q((char)vowel) == FALSE || tone_Q((char)tone) == FALSE ||
        consonant_Q((char)consonant_three) == FALSE) {
      code_exit;
    }
    assert(consonant_Q((char)consonant_two) == TRUE);
    assert(vowel_Q((char)vowel) == TRUE);
    assert(tone_Q((char)tone) == TRUE);
    assert(consonant_Q((char)consonant_three) == TRUE);
  }
  if (consonant_one != 0 && type != SHORT_ROOT) {
    code_ACC_consonant_one(type, consonant_one, &number);
    // printf("c1 %X\n", (uint) number);
  }
  if (consonant_two != 0) {
    code_ACC_consonant_two(type, consonant_two, &number);
    // printf("c2 %X\n", (uint) number);
  }
  code_ACC_vowel(type, vowel, &number);
  // printf("v %X\n", (uint) number);
  if (tone != 0) {
    code_ACC_tone(type, tone, &number);
    // printf("tone %X\n", (uint) number);
  } else {
    code_ACC_tone(type, 'M', &number);
  }
  if (consonant_three != 0 && type != LONG_GRAMMAR) {
    code_ACC_consonant_three(type, consonant_three, tone, &number);
    // printf("c3 %X\n", (uint) number);
  }
  *DAT_number = number;
}

void code_ACC_word_PL(const uint8_t ACC_GEN_magnitude,
                      const char *ACC_independentClause,
                      uint8_t *DAT_GEN_magnitude,
                      uint16_t *DAT_code_independentClause,
                      uint8_t *DAT_GEN_remainder) {
  /* identify if two glyph or four glyph word
      if there is a bad parse
      then return an error message,
          which indicates the location of the error.
  assumptions:
      this is can be used in a reduce like manner,
      so many function together, which is enabled if size is
      full width, or 0xFF the last two glyphs can
      overlap with next independentClause, so if they are a four glyph word
      then keep them, otherwise ignore.
  algorithm:
  */
  char DAT_word[WORD_LONG];
  uint8_t DAT_word_GEN_magnitude = WORD_LONG;
  uint8_t i = 0;
  uint8_t j = 0;
  uint16_t number = 0;
  // uint8_t size = ACC_GEN_magnitude;
  // if (ACC_GEN_magnitude == 0xFF) { // see assumptions
  //    size = 0xFF - 2;
  //}
  memset(DAT_word, 0, WORD_LONG);
  assert(ACC_independentClause != NULL);
  assert(ACC_GEN_magnitude > 0);
  assert(DAT_code_independentClause != NULL);
  assert(*DAT_GEN_magnitude >= ACC_GEN_magnitude / 2);
  for (; i < ACC_GEN_magnitude; j++) {
    derive_first_word((uint8_t)(ACC_GEN_magnitude - i),
                      ACC_independentClause + i, &DAT_word_GEN_magnitude,
                      DAT_word);
    // printf("%s %d \n", ACC_independentClause +i,
    //    (int) DAT_word_GEN_magnitude);
    if (DAT_word_GEN_magnitude == 0) {
      *DAT_GEN_remainder = (uint8_t)(ACC_GEN_magnitude - i);
      break;
    }
    word_number_encode(DAT_word_GEN_magnitude, DAT_word, &number);
    i = (uint8_t)(i + DAT_word_GEN_magnitude);
    DAT_code_independentClause[j] = number;
    DAT_word_GEN_magnitude = WORD_LONG;
  }
  *DAT_GEN_magnitude = j;
}

/* remember if binary_phrase_list beginning is one
    then is last tablet or only of independentClause
    else if binary_phrase_list begining is zero,
    then is part tablet of independentClause
*/
extern inline void establish_ACC_binary_phrase_list(
    const uint16_t *code_text, const uint8_t independentClause_magnitude,
    uint16_t *binary_phrase_list, uint16_t *tablet) {
  uint8_t current = 0;
  uint8_t i = 0;
  assert(code_text != NULL);
  assert(independentClause_magnitude != 0);
  assert(independentClause_magnitude <=
         TABLET_WORD_LONG * MAX_INDEPENDENTCLAUSE_TABLET + 1);
  assert(binary_phrase_list != NULL);
  if (*binary_phrase_list == 0) {
    current = (uint8_t)~current;
  }
  for (i = 0; i < independentClause_magnitude; i++) {
    if (current == 2)
      break;
    switch (current) {
    /*case 0:
        *binary_phrase_list |= 0 << (i + 1);
        break; */
    case 0xFF:
      *binary_phrase_list = (uint16_t)(*binary_phrase_list | (1 << (i + 1)));
      break;
    default:
      break;
    }
    tablet[i + 1] = code_text[i];
    switch (code_text[i]) {
    case accusative_case_GRAMMAR:
      current = (uint8_t)(~current);
      break;
    case instrumental_case_GRAMMAR:
      current = (uint8_t)(~current);
      break;
    case dative_case_GRAMMAR:
      current = (uint8_t)(~current);
      break;
    case vocative_case_GRAMMAR:
      current = (uint8_t)(~current);
      break;
    case deontic_mood_GRAMMAR:
      current = 2;
      break;
    case realis_mood_GRAMMAR:
      current = 2;
      break;
    default:
      break;
    }
  }
  tablet[0] = *binary_phrase_list;
}
void tablet_encoding(const uint8_t code_text_magnitude,
                     const uint16_t *code_text, uint8_t *tablet_magnitude,
                     uint16_t *tablet, uint8_t *remainder) {
  uint16_t binary_phrase_list = 0;
  uint8_t i = 0;
  uint8_t independentClause_magnitude = 0;
  uint8_t tablet_number = 0;
  assert(code_text != NULL);
  assert(code_text_magnitude > 0);
  assert(tablet != NULL);
  assert(tablet_magnitude != NULL);
  assert(remainder != NULL);
  assert(*tablet_magnitude >= 16);
  /* algorithm:
      detect end of independentClause marker deontic-mood,
      set remainder as the rest.
      determine if can fit in one tablet or need multiple*/
  for (i = 0; i < code_text_magnitude; i++) {
    if (code_text[i] == deontic_mood_GRAMMAR ||
        code_text[i] == realis_mood_GRAMMAR) {
      independentClause_magnitude = (uint8_t)(i + 1);
      break;
    }
  }
  assert(independentClause_magnitude > 0);
  for (i = 0; i < independentClause_magnitude;
       i = (uint8_t)(i + TABLET_WORD_LONG)) {
    if (independentClause_magnitude - i > TABLET_WORD_LONG) {
      binary_phrase_list = 0;
    } else {
      binary_phrase_list = 1;
    }
    establish_ACC_binary_phrase_list(
        code_text + i, (uint8_t)(independentClause_magnitude - i),
        &binary_phrase_list, tablet + tablet_number);
    ++tablet_number;
  }
  *remainder = (uint8_t)(code_text_magnitude - independentClause_magnitude);
  *tablet_magnitude = (uint8_t)(tablet_number);
}

extern inline void detect_ACC_quote_magnitude(const uint8_t text_magnitude,
                                              const char *text,
                                              uint8_t *quote_magnitude,
                                              uint8_t *quote_indexFinger) {
  uint8_t class_magnitude = 0;
  uint8_t text_indexFinger = 0;
  uint8_t class_indexFinger = 0;
  uint8_t found = FALSE;
  assert(text != NULL);
  assert(text_magnitude > 0);
  assert(quote_indexFinger != 0);
  assert(quote_magnitude != NULL);
  /* algorithm:
      detect silence glyph surrounding quote class word
      search for same word to conclude quote
      answer quote_indexFinger and quote_magnitude*/
  // assure silence glyph at zero indexFinger
  assert(text[0] == SILENCE_GLYPH);
  ++class_magnitude;
  // detect size of class word
  for (text_indexFinger = 1; text_indexFinger < text_magnitude;
       ++text_indexFinger) {
    ++class_magnitude;
    if (text[text_indexFinger] == SILENCE_GLYPH) {
      break;
    }
  }
  // printf("class_magnitude %X\n", (uint)class_magnitude);
  *quote_indexFinger = class_magnitude;
  // detect next class word COM quote word
  for (text_indexFinger = class_magnitude; text_indexFinger < text_magnitude;
       ++text_indexFinger) {
    if (text_indexFinger + class_magnitude > text_magnitude) {
      *quote_magnitude = 0;
      break;
    }
    for (class_indexFinger = 0; class_indexFinger <= class_magnitude;
         ++class_indexFinger) {
      if (class_indexFinger == class_magnitude) {
        // found
        *quote_magnitude = (uint8_t)(text_indexFinger - class_magnitude);
        found = TRUE;
      }
      if (text[text_indexFinger + class_indexFinger] !=
          text[class_indexFinger]) {
        break;
      }
    }
    if (found == TRUE) {
      break;
    }
  }
}

extern inline void derive_quote_code(const uint8_t quote_class_magnitude,
                                     const char *quote_class,
                                     const uint8_t quote_magnitude,
                                     const char *quote_text,
                                     uint16_t *quote_word) {
  char word[WORD_LONG];
  uint16_t quote_number = 0;
  uint8_t word_magnitude = WORD_LONG;
  memset(word, 0, WORD_LONG);
  // printf("quote_class_magnitude %X\n", (uint)quote_class_magnitude);
  assert(quote_class != NULL);
  assert(quote_class_magnitude > 0);
  assert(quote_magnitude > 0);
  assert(quote_magnitude < 16);
  assert(quote_word != NULL);
  if (quote_magnitude == 1) {
    *quote_word = (uint16_t)(QUOTED_DENOTE |
                             ((quote_text[0] - 0x30) << QUOTED_LITERAL_BEGIN));
    return;
  } else if (quote_magnitude == 2) {
    *quote_word =
        (uint16_t)QUOTED_DENOTE | (TWO_BYTE_QUOTED << CONSONANT_ONE_THICK);
  } else if (quote_magnitude > 2 && quote_magnitude <= 4) {
    *quote_word =
        (uint16_t)QUOTED_DENOTE | (FOUR_BYTE_QUOTED << CONSONANT_ONE_THICK);
  } else if (quote_magnitude > 4 && quote_magnitude <= 8) {
    *quote_word =
        (uint16_t)QUOTED_DENOTE | (EIGHT_BYTE_QUOTED << CONSONANT_ONE_THICK);
  } else if (quote_magnitude > 8 && quote_magnitude <= 16) {
    *quote_word =
        (uint16_t)QUOTED_DENOTE | (SIXTEEN_BYTE_QUOTED << CONSONANT_ONE_THICK);
  }
  // constant data
  *quote_word |= QUOTED_LITERAL << QUOTED_LITERAL_XOR_ADDRESS_BEGIN;
  *quote_word |= FALSE << QUOTED_INTEGER_BEGIN;
  derive_first_word(quote_class_magnitude, quote_class, &word_magnitude, word);
  assert(word_magnitude > 0 && "to derive type of quote");
  if (word_magnitude > 0)
    word_number_encode(word_magnitude, word, &quote_number);
  else {
    *quote_word = 0;
    return;
  }
  // printf("quote_number %X\n", (uint) quote_number);
  switch (quote_number) {
  case text_GRAMMAR:
    *quote_word |= SINGLE_BYTE_QUOTED << QUOTED_GLYPH_THICK_BEGIN;
    *quote_word |= TEXT_CLASS << QUOTED_CLASS_BEGIN;
    break;
  case number_GRAMMAR:
    *quote_word |= NUMBER_CLASS << QUOTED_CLASS_BEGIN;
    break;
  default:
    // printf("unknown quote_number %X\n", (uint)quote_number);
    assert(1 == 0);
    break;
  }
}

extern inline void fit_quote_magnitude(const uint8_t quote_magnitude,
                                       uint8_t *quote_tablet_magnitude) {
  assert(quote_tablet_magnitude != NULL);
  assert(quote_magnitude > 0);
  assert(quote_magnitude < 16);
  if (quote_magnitude == 1) {
    *quote_tablet_magnitude = 0x0;
  } else if (quote_magnitude == 2) {
    *quote_tablet_magnitude = 0x1;
  } else if (quote_magnitude > 2 && quote_magnitude <= 4) {
    *quote_tablet_magnitude = 0x2;
  } else if (quote_magnitude > 4 && quote_magnitude <= 8) {
    *quote_tablet_magnitude = 0x4;
  } else if (quote_magnitude > 8 && quote_magnitude <= 16) {
    *quote_tablet_magnitude = 0x8;
  }
}

extern void convert_last_number_to_quote(uint8_t *terminator_indexFinger,
                                         v16us *tablet) {
  uint8_t tablet_indexFinger;
  uint8_t number_indexFinger = 0;
  uint64_t number = 0;
  uint8_t finish = FALSE;
  uint16_t indicator_list = (uint16_t)tablet[0].s0;
  uint8_t indicator = indicator_list & 1;
  uint8_t retrospective_phrase_indexFinger = *terminator_indexFinger - 1;
  assert(*terminator_indexFinger > 0);
  assert(tablet != NULL);
  // find last phrase indexFinger
  for (; retrospective_phrase_indexFinger < *terminator_indexFinger;
       --retrospective_phrase_indexFinger) {
    if (((indicator_list >> retrospective_phrase_indexFinger) & 1) ==
        indicator) {
      // found last phrase
      break;
    }
  }
  tablet_indexFinger = *terminator_indexFinger;
  for (; tablet_indexFinger > 0; --tablet_indexFinger) {
    // printf("word %X ", (uint) tablet[0][tablet_indexFinger-1]);
    switch (((uint16_t *)(tablet))[tablet_indexFinger - 1]) {
    case zero_WORD:
      ++number_indexFinger;
      break;
    case one_WORD:
      number |= (uint64_t)(1 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case two_WORD:
      number |= (uint64_t)(2 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case three_WORD:
      number |= (uint64_t)(3 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case four_WORD:
      number |= (uint64_t)(4 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case five_WORD:
      number |= (uint64_t)(5 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case six_WORD:
      number |= (uint64_t)(6 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case seven_WORD:
      number |= (uint64_t)(7 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case eight_WORD:
      number |= (uint64_t)(8 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case nine_WORD:
      number |= (uint64_t)(9 << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case ten_WORD:
      number |= (uint64_t)(0xA << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case eleven_WORD:
      number |= (uint64_t)(0xB << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case twelve_WORD:
      number |= (uint64_t)(0xC << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case thirteen_WORD:
      number |= (uint64_t)(0xD << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case fourteen_WORD:
      number |= (uint64_t)(0xE << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    case fifteen_WORD:
      number |= (uint64_t)(0xF << number_indexFinger * 4);
      ++number_indexFinger;
      break;
    default:
      finish = TRUE;
      break;
    }
    if (finish == TRUE)
      break;
  }
  /* set up quote and number if necessary (number_indexFinger > 2)*/
  // printf("number %X, tablet_indexFinger %X, number_indexFinger %X\n",
  // (uint)number,
  //       (uint)tablet_indexFinger, (uint)number_indexFinger);
  // printf("number %lX\n", number);
  if (number <= 0xFFFF) {
    // printf("RPI %X\n", retrospective_phrase_indexFinger);
    v16us_write(retrospective_phrase_indexFinger,
                (uint16_t)(SHORT_NUMBER_QUOTED), tablet);
    ++retrospective_phrase_indexFinger;
    v16us_write(retrospective_phrase_indexFinger, (uint16_t)(number), tablet);
    *terminator_indexFinger = (uint8_t)(retrospective_phrase_indexFinger);
    // printf("RPI %X\n", retrospective_phrase_indexFinger);
  }
  assert(number_indexFinger <= 2);
}

void v4us_write(uint8_t code_indexFinger, uint8_t maximum_code_indexFinger,
                uint16_t code_number, v4us *code_name) {
  if (code_indexFinger >= maximum_code_indexFinger)
    return;
  else if (code_indexFinger == 0) {
    (*code_name).s0 = code_number;
  } else if (code_indexFinger == 1) {
    (*code_name).s1 = code_number;
  } else if (code_indexFinger == 2)
    (*code_name).s2 = code_number;
}
uint16_t v16us_read(const uint8_t indexFinger, const v16us vector) {
  assert(indexFinger < 16);
  switch (indexFinger) {
  case 0:
    return (uint16_t)vector.s0;
    break;
  case 1:
    return (uint16_t)vector.s1;
    break;
  case 2:
    return (uint16_t)vector.s2;
    break;
  case 3:
    return (uint16_t)vector.s3;
    break;
  case 4:
    return (uint16_t)vector.s4;
    break;
  case 5:
    return (uint16_t)vector.s5;
    break;
  case 6:
    return (uint16_t)vector.s6;
    break;
  case 7:
    return (uint16_t)vector.s7;
    break;
  case 8:
    return (uint16_t)vector.s8;
    break;
  case 9:
    return (uint16_t)vector.s9;
    break;
  case 0xA:
    return (uint16_t)vector.sa;
    break;
  case 0xB:
    return (uint16_t)vector.sb;
    break;
  case 0xC:
    return (uint16_t)vector.sc;
    break;
  case 0xD:
    return (uint16_t)vector.sd;
    break;
  case 0xE:
    return (uint16_t)vector.se;
    break;
  case 0xF:
    return (uint16_t)vector.sf;
    break;
  default:
    assert(1 == 0); //"invalid value"
  }
}

#define independentClause_encoding_mood                                        \
  v16us_write(tablet_indexFinger, number, tablet);                             \
  binary_phrase_list =                                                         \
      (uint16_t)(binary_phrase_list ^ (1 << tablet_indexFinger));              \
  current = 2;                                                                 \
  ++tablet_indexFinger;                                                        \
  break;

#define independentClause_encoding_case                                        \
  binary_phrase_list =                                                         \
      (uint16_t)(binary_phrase_list ^ (1 << tablet_indexFinger));              \
  v16us_write(tablet_indexFinger, number, tablet);                             \
  ++tablet_indexFinger;                                                        \
  break;

void word_series_encode(const uint16_t text_long, const char *text,
                        uint16_t *word_series_long, uint16_t *word_series) {
  assert(word_series != NULL);
  assert(word_series_long != NULL);
  assert(*word_series_long > 0);

  // till end of text
  uint16_t text_indexFinger = 0;
  uint16_t word_series_indexFinger = 0;
  uint8_t word_long = 0;
  uint16_t word_begin = 0;
  uint16_t word_number = 0;
  for (word_series_indexFinger = 0;
       word_series_indexFinger < *word_series_long &&
       text_long - text_indexFinger > 1;
       ++word_series_indexFinger) {
    printf("%s:%d:\ttext_indexFinger 0x%X text_long 0x%X text %s\n", __FILE__,
           __LINE__, text_indexFinger, text_long - text_indexFinger,
           text + text_indexFinger);
    first_word_derive((uint8_t)(text_long - text_indexFinger),
                      text + text_indexFinger, &word_long, &word_begin);
    if (word_long == 0) {
      break;
    }
    text_indexFinger += word_begin;
    word_number_encode(word_long, text + text_indexFinger, &word_number);
    word_series[word_series_indexFinger] = word_number;
    text_indexFinger += word_long;
  }
  // get words
  // add to array
  // return  length
  *word_series_long = word_series_indexFinger;
}

uint8_t vector_long_find(uint16_t number) {
  if (number < 5)
    return (uint8_t)number;
  if (number <= 8)
    return 8;
  if (number <= 16)
    return 16;
  return 0;
}

uint16_t vector_code(uint8_t vector_long) {
  if (vector_long == 1)
    return VECTOR_THICK_1;
  if (vector_long == 2)
    return VECTOR_THICK_2;
  if (vector_long == 3)
    return VECTOR_THICK_3;
  if (vector_long == 4)
    return VECTOR_THICK_4;
  if (vector_long == 8)
    return VECTOR_THICK_8;
  if (vector_long == 16)
    return VECTOR_THICK_16;
  assert(1 == 0);
  return 0;
}

void independentClause_encoding(const uint16_t text_magnitude, const char *text,
                                uint8_t *tablet_magnitude, v16us *tablet,
                                uint16_t *text_remainder) {
  /* algorithm:
      loop through glyphs,
      derive words
      if word is quote then add it to tablet,
          and add proper quote identifier.
      if word is accusative, instrumental, or dative,
          flip the index representation for it.
      if word is deontic-mood then set as ending tablet.
      otherwise add word as name
  */
  char glyph;
  uint8_t text_indexFinger = 0;
  uint8_t tablet_indexFinger = 1;
  uint8_t quote_indexFinger = 0;
  char word[WORD_LONG];
  uint8_t word_magnitude = 0;
  char derived_word[WORD_LONG];
  uint8_t derived_word_magnitude = WORD_LONG;
  uint16_t number = 0;
  uint16_t quote_word = 0;
  uint16_t binary_phrase_list = (uint16_t)1;
  uint8_t quote_magnitude = 0;
  // uint8_t quote_tablet_magnitude = 0;
  uint8_t current = 0x0;
  uint8_t word_long = 0;
  uint16_t word_begin = 0;
  uint16_t quote_sort_code = 0;
  uint16_t quote_sort = 0;
  uint16_t scalar_thick = 0;
  uint16_t word_series[MAXIMUM_WORD_SERIES_LONG] = {0};
  uint16_t word_series_long = MAXIMUM_WORD_SERIES_LONG;
  uint8_t vector_long = 0;
  uint16_t series_indexFinger = 0;
  memset(word, 0, WORD_LONG);
  memset(derived_word, 0, WORD_LONG);
  assert(text != NULL);
  assert(text_magnitude > 0);
  assert(tablet != NULL);
  assert(tablet_magnitude != NULL);
  assert(text_remainder != NULL);
  // printf("tablet_magnitude %X text %s\n",(uint) *tablet_magnitude, text);
  // assert(*tablet_magnitude >= text_magnitude/2/15
  // /*MAX_INDEPENDENTCLAUSE_TABLET*/);
  // printf("independentClause encoding\n");
  for (text_indexFinger = 0; text_indexFinger < text_magnitude;
       ++text_indexFinger) {
    glyph = text[text_indexFinger];
    // printf("%s:%d:\t text_magnitude 0x%X text %s\n", __FILE__, __LINE__,
    //       text_magnitude, text + text_indexFinger);
    // printf("%s:%d:\t letter %c\n", __FILE__, __LINE__, glyph);
    if (glyph == 0) {
      assert(1 == 0);
    }
    if (consonant_Q(glyph) == TRUE || vowel_Q(glyph) == TRUE ||
        tone_Q(glyph) == TRUE) {
      word[word_magnitude] = glyph;
      // printf("%c", glyph);
      word_magnitude = (uint8_t)(word_magnitude + 1);
    }
    if (word_magnitude >= 2) {
      // printf("tablet_indexFinger %X\n", (uint) tablet_indexFinger);
      memset(derived_word, 0, WORD_LONG);
      derived_word_magnitude = WORD_LONG;
      derive_first_word(word_magnitude, word, &derived_word_magnitude,
                        derived_word);
      if (derived_word_magnitude > 0) {
        number = 0;
        word_number_encode(derived_word_magnitude, derived_word, &number);
        // printf("n 0x%X \n", (uint) number);
        if (number != 0) {
          memset(word, 0, WORD_LONG);
          switch (number) {
          case number_GRAMMAR:
            /* if preceded by a quote word, then do as a default.
               if preceded by numbers then convert them to a quote,
               and adjust tablet_indexFinger accordingly */
            if ((v16us_read(tablet_indexFinger - 1, *tablet) & QUOTED_DENOTE) ==
                QUOTED_DENOTE) {
              // tablet[0][tablet_indexFinger] = number;
              //++tablet_indexFinger;
              break;
            } else {
              // convert last of tablet to number quote
              // printf("pre tablet_indexFinger %X\n",
              // (uint)tablet_indexFinger);
              convert_last_number_to_quote(&tablet_indexFinger, tablet);
              // printf("post tablet_indexFinger %X\n",
              // (uint)tablet_indexFinger);
              // tablet[0][tablet_indexFinger] = number;
              ++tablet_indexFinger;
              break;
            }
          case text_GRAMMAR:
            printf("%s:%d\t TODO text grammar quote \n", __FILE__, __LINE__);
            //
            break;
          case word_GRAMMAR:
            printf("%s:%d\t TODO word grammar quote \n", __FILE__, __LINE__);
            //  find next word grammar
            // encode text between
            // create applicable type
            // adjust applicable indexFingers
            break;
          case quoted_GRAMMAR:
            // printf("detected quote word %X\n", (uint)text_indexFinger);
            ++text_indexFinger;
            quote_word = 0;
            detect_ACC_quote_magnitude(
                (uint8_t)(text_magnitude - text_indexFinger),
                text + text_indexFinger, &quote_magnitude, &quote_indexFinger);
            printf("%s:%d\tdetected quote size 0x%X indexFinger 0x%X \n",
                   __FILE__, __LINE__, (uint)quote_magnitude,
                   quote_indexFinger);
            // printf("quote_indexFinger %X\n", (uint) quote_indexFinger -
            // text_indexFinger);
            // printf("quote %s\n", text + text_indexFinger +
            // SILENCE_GLYPH_LONG);

            // encode the quote sort word, then switch case it
            //  find quote sort word
            text_indexFinger += SILENCE_GLYPH_LONG;
            printf("%s:%d\tletter %c\n", __FILE__, __LINE__,
                   text[text_indexFinger]);
            first_word_derive(WORD_LONG, text + text_indexFinger, &word_long,
                              &word_begin);
            printf("%s:%d\tletter %c word_long 0x%X\n", __FILE__, __LINE__,
                   text[text_indexFinger + word_begin], word_long);
            word_number_encode(word_long, text + text_indexFinger + word_begin,
                               &quote_sort_code);
            printf("%s:%d\tquote_sort_code %X\n", __FILE__, __LINE__,
                   quote_sort_code);
            switch (quote_sort_code) {
            case word_GRAMMAR:
              printf("%s:%d\tword quote detected\n", __FILE__, __LINE__);
              quote_word = QUOTE_DENOTE;
              quote_sort = WORD_SORT_DENOTE;
              quote_word |= quote_sort << SORT_DENOTE_BEGIN;
              printf("%s:%d\tquote_word 0x%X\n", __FILE__, __LINE__,
                     quote_word);
              scalar_thick = SIXTEEN_TIDBIT_SCALAR_THICK;
              quote_word |= scalar_thick << SCALAR_THICK_BEGIN;
              // find length till next quote_sort_code
              printf("%s:%d\tquote_word 0x%X\n", __FILE__, __LINE__,
                     quote_word);
              // quote_indexFinger and quote_magnitude tell me
              text_indexFinger += quote_indexFinger - SILENCE_GLYPH_LONG;
              // encode them as words
              // convert words into array,
              word_series_encode(quote_magnitude, text + text_indexFinger,
                                 &word_series_long, word_series);
              printf("%s:%d\tword_series_long 0x%X\n", __FILE__, __LINE__,
                     word_series_long);
              // find the best vector size for them
              vector_long = vector_long_find(word_series_long);
              printf("%s:%d\tvector_long 0x%X\n", __FILE__, __LINE__,
                     vector_long);
              // set length appropriately
              printf("%s:%d\tquote_word 0x%X\n", __FILE__, __LINE__,
                     quote_word);
              quote_word |= vector_code(vector_long) << VECTOR_THICK_BEGIN;
              printf("%s:%d\tquote_word 0x%X\n", __FILE__, __LINE__,
                     quote_word);
              // append the quote and words to the tablet
              v16us_write(tablet_indexFinger, quote_word, tablet);
              ++tablet_indexFinger;
              for (series_indexFinger = 0;
                   series_indexFinger < word_series_long;
                   ++series_indexFinger) {
                v16us_write(tablet_indexFinger, word_series[series_indexFinger],
                            tablet);
                ++tablet_indexFinger;
              }
              // leave the encoded place and text place properly
              text_indexFinger += quote_magnitude + SILENCE_GLYPH_LONG * 2 +
                                  word_long + QUOTED_WORD_LONG - 1;
              printf("%s:%d\ttext %s\n", __FILE__, __LINE__,
                     text + text_indexFinger);
              break;
            case number_GRAMMAR:
              printf("%s:%d\tnumber quote detected\n", __FILE__, __LINE__);
              break;
            case independent_clause_GRAMMAR:
              printf("%s:%d\tsentence quote detected\n", __FILE__, __LINE__);
              break;
            }
            //          derive_quote_code(
            //              (uint8_t)(quote_indexFinger - SILENCE_GLYPH_LONG),
            //              text + text_indexFinger + SILENCE_GLYPH_LONG,
            //              quote_magnitude,
            //              text + text_indexFinger + quote_indexFinger,
            //              &quote_word);
            // printf("quote_word %X\n", (uint)quote_word);
            //((uint16_t *)tablet)[tablet_indexFinger] = quote_word;
            // v16us_write(tablet_indexFinger, quote_word, tablet);
            //++tablet_indexFinger;
            // copy_ACC_text_DAT_tablet(
            //    text + text_indexFinger + quote_indexFinger, quote_magnitude,
            //    tablet, tablet_indexFinger,
            //    (uint8_t)(*tablet_magnitude * TABLET_LONG -
            //              tablet_indexFinger));
            //// printf("text_indexFinger %X, quote_indexFinger %X,
            //// quote_magnitude
            //// %X\n",
            ////       (uint)text_indexFinger, (uint)quote_indexFinger,
            ////       (uint)quote_magnitude);
            // text_indexFinger =
            //    (uint8_t)(text_indexFinger + (quote_indexFinger)*2 +
            //              QUOTED_WORD_LONG + quote_magnitude - 1);
            // word_magnitude = 0;
            // fit_quote_magnitude(quote_magnitude, &quote_tablet_magnitude);
            //// printf("qll %X\n", (uint)
            ////     quote_tablet_magnitude);
            // tablet_indexFinger =
            //    (uint8_t)(tablet_indexFinger + quote_tablet_magnitude);
            ////    printf("ls %X\n", (uint)
            ////        tablet_indexFinger);
            break;

          case nominative_case_GRAMMAR:
            independentClause_encoding_case;
          case accusative_case_GRAMMAR:
            independentClause_encoding_case;
          case instrumental_case_GRAMMAR:
            independentClause_encoding_case;
          case topic_case_GRAMMAR:
            independentClause_encoding_case;
          case dative_case_GRAMMAR:
            independentClause_encoding_case;
          case vocative_case_GRAMMAR:
            independentClause_encoding_case;
          case conditional_mood_GRAMMAR:
            v16us_write(tablet_indexFinger, number, tablet);
            binary_phrase_list =
                (uint16_t)(binary_phrase_list ^ (1 << tablet_indexFinger));
            ++tablet_indexFinger;
            break;
          case deontic_mood_GRAMMAR:
            independentClause_encoding_mood;
          case realis_mood_GRAMMAR:
            independentClause_encoding_mood;
          case return_GRAMMAR:
            independentClause_encoding_mood;
          case finally_GRAMMAR:
            independentClause_encoding_mood;
          default:
            v16us_write(tablet_indexFinger, number, tablet);
            ++tablet_indexFinger;
            break;
          }
          if (current == 2)
            break;
          word_magnitude = 0;
        } else {
        }
      }
    }
  }
  ++text_indexFinger;
  // printf("se text_indexFinger %X\n", (uint)text_indexFinger);
  *tablet_magnitude = 1;
  *text_remainder = (uint16_t)(text_magnitude - text_indexFinger);
  v16us_write(0, binary_phrase_list, tablet);
}
inline void play(const v4us coded_name, v8us *hook_list) {
  void *accusative = NULL;
  void *instrumental = NULL;
  // void *dative =  NULL;
  assert(((uint16_t *)&coded_name)[VERB_INDEXFINGER] != 0);
  assert(hook_list != NULL);
  // quizing hash key name
  printf("coded_name play %04X%04X%04X%04X\n",
         (uint)((uint16_t *)&coded_name)[3], (uint)((uint16_t *)&coded_name)[2],
         (uint)((uint16_t *)&coded_name)[1],
         (uint)((uint16_t *)&coded_name)[0]);
  // switch (coded_name[ACCUSATIVE_INDEXFINGER]) {
  // case UNSIGNED_CHAR_QUOTED:
  //  accusative = (unsigned char *)&(hook_list[ACCUSATIVE_INDEXFINGER]);
  //  break;
  // case SIGNED_CHAR_QUOTED:
  //  accusative = (char *)&(hook_list[ACCUSATIVE_INDEXFINGER]);
  //  break;
  // case SHORT_NUMBER_QUOTED:
  //  accusative = (uint16_t *)&(hook_list[ACCUSATIVE_INDEXFINGER]);
  //  break;
  // case ERROR_BINARY:
  //  break;
  // default:
  //  printf("unrecognized type %04X",
  //  (uint)coded_name[ACCUSATIVE_INDEXFINGER]);
  //  assert(0 != 0);
  //  break;
  //}
  switch (((uint16_t *)&coded_name)[INSTRUMENTAL_INDEXFINGER]) {
  case UNSIGNED_CHAR_QUOTED:
    instrumental = (unsigned char *)&(hook_list[INSTRUMENTAL_INDEXFINGER]);
    break;
  case SIGNED_CHAR_QUOTED:
    instrumental = (char *)&(hook_list[INSTRUMENTAL_INDEXFINGER]);
    break;
  case SHORT_NUMBER_QUOTED:
    instrumental = (uint16_t *)&(hook_list[INSTRUMENTAL_INDEXFINGER]);
    break;
  case ERROR_BINARY:
    break;
  default:
    printf("unrecognized type %04X",
           (uint)((uint16_t *)&coded_name)[ACCUSATIVE_INDEXFINGER]);
    assert(0 != 0);
    break;
  }
  switch (*((uint64_t *)&coded_name)) {
  case 0x6048009D00000000: /* say unsigned char* */
    x6048009D00000000((unsigned char *)accusative);
    break;
  case 0x6048029D00000000: /* say signed char* */
    x6048029D00000000((signed char *)accusative);
    break;
  case 0x4124000000000000: /* equal */
    x4124000000000000((v8us *)hook_list);
    break;
  case 0x8006000000000000: /* different */
    x8006000000000000((v8us *)hook_list);
    break;
  case 0xA130143D143D0000: /* not CCNOT */
    xA130143D143D0000((uint16_t *)accusative, (uint16_t *)instrumental);
    break;
  case 0xC450143D143D0000: /* not CCNOT */
    xC450143D143D0000((uint16_t *)accusative, (uint16_t *)instrumental);
    break;
  case 0x8006143D143D0000: /* not CCNOT */
    x8006143D143D0000((uint16_t *)accusative, (uint16_t *)instrumental);
    break;
  default:
    printf(
        "unrecognized coded_name %04X%04X%04X%04X\n",
        (uint)((uint16_t *)&coded_name)[3], (uint)((uint16_t *)&coded_name)[2],
        (uint)((uint16_t *)&coded_name)[1], (uint)((uint16_t *)&coded_name)[0]);
    assert(0 != 0);
    break;
  }
}
extern inline void play_quote(const v16us *tablet,
                              const uint8_t tablet_indexFinger,
                              const uint8_t tablet_magnitude,
                              uint16_t *quote_word, v8us *quote_fill) {
  uint16_t word;
  uint8_t quote_indexFinger = 0;
  uint8_t quote_magnitude;
  assert(tablet != NULL);
  assert(tablet_indexFinger < TABLET_LONG);
  assert(tablet_magnitude < MAX_INDEPENDENTCLAUSE_TABLET);
  assert(quote_word != NULL);
  assert(quote_fill != NULL);
  word = v16us_read(tablet_indexFinger, *tablet);
  // printf("quote quizing, word %04X\n", (uint) (*tablet)[tablet_indexFinger]);
  if ((word & CONSONANT_ONE_MASK) == QUOTED_DENOTE) {
    // then is quote
    *quote_word = word;
    // printf("quote detected %04X\n", (uint)word);
    quote_magnitude = (uint8_t)(
        1 << (((*quote_word >> CONSONANT_ONE_THICK) & 7 /* 3 bit mask */) - 1));
    // printf("quote_magnitude %X \n", (uint)quote_magnitude);
    // printf("tablet_indexFinger %X \n", (uint)tablet_indexFinger);
    assert(quote_magnitude < tablet_magnitude * TABLET_LONG * WORD_THICK);
    // printf("quote_fill ");
    if (quote_magnitude == 0) {
      ((uint16_t *)quote_fill)[0] = (uint16_t)(word >> QUOTED_LITERAL_BEGIN);
      // printf("%04X ", (uint)(*quote_fill)[0]);
    }
    for (quote_indexFinger = 0; quote_indexFinger < quote_magnitude;
         ++quote_indexFinger) {
      ((uint16_t *)quote_fill)[quote_indexFinger] =
          v16us_read(tablet_indexFinger + quote_indexFinger + 1, *tablet);
      // printf("%04X ", (uint)(*quote_fill)[quote_indexFinger]);
    }
    // printf("\n");
  }
}
void burden_hook_list(const uint8_t tablet_magnitude, const v16us *tablet,
                      uint8_t *tablet_indexFinger, v4us *coded_name,
                      v8us *hook_list) {
  assert(tablet_magnitude != 0);
  assert(tablet != NULL);
  assert(coded_name != NULL);
  assert(hook_list != NULL);
  assert(tablet_indexFinger != NULL);
  assert(*tablet_indexFinger >= 1);
  uint16_t indicator_list = 0;
  uint8_t indicator = 0;
  uint8_t tablet_number = 0;
  uint8_t exit = FALSE;
  uint16_t word = 0;
  uint16_t quote_word = 0;
  v8us quote_fill = {{0}};
  indicator_list = v16us_read(0, *tablet);
  indicator = (uint8_t)1 & indicator_list;
  // printf("indicator %X\n", (uint) indicator);
  // printf("indicator_list %X\n", (uint) indicator_list);
  for (tablet_number = 0; tablet_number < tablet_magnitude; ++tablet_number) {
    for (; *tablet_indexFinger < TABLET_LONG; ++*tablet_indexFinger) {
      // printf("BHL tablet_indexFinger %X\n", (uint)*tablet_indexFinger);
      // if previous is indicated then quiz if is quote
      if (((indicator_list & (1 << (*tablet_indexFinger - 1))) >>
           (*tablet_indexFinger - 1)) == indicator) {
        // printf("quote's word %X \n", (uint)tablet[0][*tablet_indexFinger]);
        play_quote(tablet, *tablet_indexFinger, tablet_magnitude, &quote_word,
                   &quote_fill);
      }
      // if current is indicated then quiz if is case or
      // verb
      if (((indicator_list & (1 << *tablet_indexFinger)) >>
           *tablet_indexFinger) == indicator) {
        word = ((uint16_t **)&tablet)[tablet_number][*tablet_indexFinger];
        // printf("BHL word %X\n", (uint)word);
        switch (word) {
        case accusative_case_GRAMMAR:
          // printf("detected accusative case\n");
          if (quote_word != 0) {
            ((uint16_t *)coded_name)[ACCUSATIVE_INDEXFINGER] = quote_word;
            // printf("coded_name ACC %04X%04X%04X%04X\n",
            //       (uint)(*coded_name)[3], (uint)(*coded_name)[2],
            //       (uint)(*coded_name)[1], (uint)(*coded_name)[0]);
            hook_list[ACCUSATIVE_INDEXFINGER] = quote_fill;
            // printf("ACC quote_fill %X\n", (uint)quote_fill[0]);
            // printf("ACC hook_list %X\n",
            // (uint)hook_list[ACCUSATIVE_INDEXFINGER][0]);
            quote_word = 0;
          }
          break;
        case dative_case_GRAMMAR:
          if (quote_word != 0) {
            ((uint16_t *)coded_name)[DATIVE_INDEXFINGER] = quote_word;
            hook_list[DATIVE_INDEXFINGER] = quote_fill;
            quote_word = 0;
          }
          break;
        case instrumental_case_GRAMMAR:
          if (quote_word != 0) {
            ((uint16_t *)coded_name)[INSTRUMENTAL_INDEXFINGER] = quote_word;
            hook_list[INSTRUMENTAL_INDEXFINGER] = quote_fill;
            quote_word = 0;
          }
          break;
        default:
          exit = TRUE;
          break;
        }
      }
      if (exit == TRUE)
        break;
    }
    if (exit == TRUE)
      break;
  }
}
void sort_code_name(v4us *code_name) {
  v4us temp = (*code_name).xyzw;
  printf("temp1 %04X %04X %04X %04X\n", (cl_ushort)temp.s0, temp.s1, temp.s2,
         temp.s3);
  if (temp.s0 > temp.s1) {
    temp = temp.s1023;
  }
  printf("temp2 %04X %04X %04X %04X\n", (cl_ushort)temp.s0, (cl_ushort)temp.s1,
         temp.s2, temp.s3);
  if (temp.s1 > temp.s2) {
    temp = temp.s0213;
  }
  printf("temp3 %04X %04X %04X %04X\n", temp.s0, temp.s1, temp.s2, temp.s3);
  if (temp.s0 > temp.s1) {
    temp = temp.s1023;
  }
  printf("temp-sort %04X %04X %04X %04X\n", temp.s0, temp.s1, temp.s2, temp.s3);
  *code_name = temp.xyzw;
}
void derive_code_name(const uint8_t tablet_magnitude, const v16us *tablet,
                      v4us *code_name) {
  assert(tablet_magnitude != 0);
  assert(tablet != NULL);
  assert(code_name != NULL);
  uint8_t tablet_indexFinger = 1;
  uint16_t indicator_list = 0;
  uint8_t indicator = 0;
  uint8_t tablet_number = 0;
  uint8_t exit = FALSE;
  uint8_t maximum_code_indexFinger = 3;
  uint16_t word = 0;
  uint16_t quote_sort = 0;
  uint8_t code_indexFinger = 0;
  // v8us quote_fill = {{0}};
  indicator_list = v16us_read(0, *tablet);
  indicator = (uint8_t)1 & indicator_list;
  // printf("indicator %X\n", (uint) indicator);
  // printf("indicator_list %X\n", (uint) indicator_list);
  //
  //
  for (tablet_number = 0; tablet_number < tablet_magnitude; ++tablet_number) {
    for (; tablet_indexFinger < TABLET_LONG; ++tablet_indexFinger) {
      // printf("BHL tablet_indexFinger %X\n", (uint)*tablet_indexFinger);
      // if previous is indicated then quiz if is quote
      quote_sort = 1;
      if (((indicator_list & (1 << (tablet_indexFinger - 1))) >>
           (tablet_indexFinger - 1)) == indicator &&
          (v16us_read(tablet_indexFinger, tablet[0]) &
           (uint16_t)CONSONANT_ONE_MASK) == (uint16_t)QUOTED_DENOTE) {
        // check if is quote, if yes then copy it over to coded name
        quote_sort = (uint16_t)(v16us_read(tablet_indexFinger, tablet[0]) >>
                                CONSONANT_ONE_THICK);
      }
      // check word before the grammatical-case, see if it is a name type.
      // if it is, then copy it over to coded name.
      // if current is indicated then quiz if is case or
      // verb
      uint16_t code_number;
      if (((indicator_list & (1 << tablet_indexFinger)) >>
           tablet_indexFinger) == indicator) {
        word = v16us_read(tablet_indexFinger, tablet[tablet_number]);
        // printf("BHL word %X\n", (uint)word);
        switch (word) {
        case nominative_case_GRAMMAR:
          printf("detected nominative case\n");
          code_number =
              (uint16_t)((SOURCE_CASE << POSTURE_TIDBIT) + quote_sort);
          v4us_write(code_indexFinger, maximum_code_indexFinger, code_number,
                     code_name);
          code_indexFinger++;
          break;
        case accusative_case_GRAMMAR:
          printf("detected accusative case\n");
          ((uint16_t *)code_name)[code_indexFinger] =
              (uint16_t)((LOCATION_CASE << POSTURE_TIDBIT) + quote_sort);
          code_indexFinger++;
          break;
        case topic_case_GRAMMAR:
          printf("detected topic case\n");
          code_number =
              (uint16_t)((WAY_CASE << POSTURE_TIDBIT) +
                         (DISCOURSE_CONTEXT << SCENE_TIDBIT) + quote_sort);
          v4us_write(code_indexFinger, maximum_code_indexFinger, code_number,
                     code_name);
          code_indexFinger++;
          break;
        case dative_case_GRAMMAR:
          if (quote_sort != 0) {
            ((uint16_t *)code_name)[DATIVE_INDEXFINGER] = quote_sort;
            // hook_list[DATIVE_INDEXFINGER] = quote_fill;
            quote_sort = 0;
          }
          break;
        case instrumental_case_GRAMMAR:
          if (quote_sort != 0) {
            ((uint16_t *)code_name)[INSTRUMENTAL_INDEXFINGER] = quote_sort;
            // hook_list[INSTRUMENTAL_INDEXFINGER] = quote_fill;
            quote_sort = 0;
          }
          break;
        default:
          exit = TRUE;
          break;
        }
      }
      if (exit == TRUE)
        break;
    }
    if (exit == TRUE)
      break;
  }
  sort_code_name(code_name);
}

int phrase_code_compare(const void *a, const void *b) {
  return (int)(*(uint16_t *)a - *(uint16_t *)b);
}

void sort_array_sort(const uint8_t array_long, uint64_t *sort_array) {
  assert(sort_array != NULL);
  qsort(sort_array, array_long - 1 /* last one is verb, don't sort it!*/,
        sizeof(uint64_t), phrase_code_compare);
}

/* implements universal hashing using random bit-vectors in x */
/* assumes number of elements in x is at least BITS_PER_CODE_NAME *
 * MAX_STRING_SIZE
 */

#define BITS_PER_CODE_NAME (64) /* not true on all machines! */
#define MAX_STRING_SIZE (16)    /* we'll stop hashing after this many */
#define MAX_BITS (BITS_PER_CODE_NAME * MAX_STRING_SIZE)
#define SEED_NUMBER UINT64_C(0x123456789ABCDEF)

uint64_t splitMix64(uint64_t *seed) {
  uint64_t z = (*seed += UINT64_C(0x9E3779B97F4A7C15));
  z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
  z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
  return z ^ (z >> 31);
}

uint64_t hash(const uint8_t array_length, const uint64_t *array) {
  uint64_t hash;
  uint8_t array_indexFinger = 0;
  /*uint8_t bit_indexFinger = 0;*/
  uint64_t random_seed = SEED_NUMBER;
  uint64_t c;
  uint64_t hash_number = 0;
  int shift;

  /* cast s to unsigned const char * */
  /* this ensures that elements of s will be treated as having values >= 0 */

  // printf("array_indexFinger %X\n", array_indexFinger);
  hash = 0;
  for (array_indexFinger = 0; array_indexFinger < array_length;
       ++array_indexFinger) {
    c = array[array_indexFinger];
    for (shift = 0; shift < BITS_PER_CODE_NAME;
         ++shift /*, ++bit_indexFinger*/) {
      /* is low bit of c set? */
      hash_number = splitMix64(&random_seed);
      if (c & 0x1) {
        hash ^= hash_number;
        // printf("hash %lX\n", hash);
      }

      /* shift c to get new bit in lowest position */
      c >>= 1;
    }
  }

  return hash;
}

void phrase_copy(const uint8_t tablet_indexFinger, const v16us tablet,
                 uint64_t *phrase) {
  // copies the remainder of phrase from back,
  //  stops if indicator says start of a phrase
  assert(phrase != NULL);
  assert(tablet_indexFinger > 0 && tablet_indexFinger < TABLET_LONG);
  const uint16_t indicator_list = (uint16_t)tablet.s0;
  const uint8_t indicator = 1 & indicator_list;
  uint16_t code_word = 0;
  uint8_t indexFinger = tablet_indexFinger - 1;
  *phrase = 0;
  *phrase = (uint64_t)v16us_read(tablet_indexFinger, tablet);
  for (; indexFinger > tablet_indexFinger - (CODE_NAME_WORD_LONG - 1);
       --indexFinger) {
    if (((indicator_list >> indexFinger) & 1) == indicator) {
      break;
    }
    code_word = v16us_read(indexFinger, tablet);
    if ((code_word & SHORT_GRAMMAR_DENOTE_MASK) == SHORT_GRAMMAR_DENOTE ||
        (code_word & LONG_GRAMMAR_DENOTE_MASK) == LONG_GRAMMAR_DENOTE) {
      *phrase |= ((uint64_t)code_word) << (CODE_WORD_TIDBIT_LONG *
                                           (tablet_indexFinger - indexFinger));
    } else {
      break;
    }
  }
}

void verb_copy(const uint8_t tablet_indexFinger, const v16us tablet,
               uint64_t *phrase) {
  // copies the remainder of phrase from back,
  //  stops if indicator says start of a phrase
  assert(phrase != NULL);
  assert(tablet_indexFinger > 0 && tablet_indexFinger < TABLET_LONG);
  const uint16_t indicator_list = (uint16_t)tablet.s0;
  const uint8_t indicator = 1 & indicator_list;
  uint8_t indexFinger = tablet_indexFinger - 1;
  *phrase = 0;
  //*phrase = (uint64_t)v16us_read(tablet_indexFinger, tablet);
  for (; indexFinger > tablet_indexFinger - (CODE_NAME_WORD_LONG - 1);
       --indexFinger) {
    if (((indicator_list >> indexFinger) & 1) == indicator) {
      break;
    }
    *phrase |=
        ((uint64_t)v16us_read(indexFinger, tablet))
        << (CODE_WORD_TIDBIT_LONG * ((tablet_indexFinger - 1) - indexFinger));
  }
}

void sort_array_establish(const uint8_t tablet_magnitude, const v16us *tablet,
                          uint8_t *sort_array_long, uint64_t *sort_array) {
  assert(sort_array_long != NULL);
  assert(sort_array != NULL);
  assert(tablet != NULL);
  assert(tablet_magnitude > 0);
  // algorithm
  // include cases, types, topic, and verb
  // include
  uint8_t tablet_indexFinger = 1;
  uint16_t indicator_list = 0;
  uint8_t indicator = 0;
  uint8_t tablet_number = 0;
  uint8_t exit = FALSE;
  uint16_t word = 0;
  uint8_t sort_array_indexFinger = 0;
  uint16_t quote_sort = 0;
  uint64_t phrase = 0;
  // uint8_t code_indexFinger = 0;
  // v8us quote_fill = {{0}};
  indicator_list = v16us_read(0, *tablet);
  indicator = (uint8_t)1 & indicator_list;
  // printf("indicator %X\n", (uint) indicator);
  // printf("indicator_list %X\n", (uint)indicator_list);
  //
  //
  for (tablet_number = 0; tablet_number < tablet_magnitude; ++tablet_number) {
    quote_sort = 0;
    for (tablet_indexFinger = 1; tablet_indexFinger < TABLET_LONG;
         ++tablet_indexFinger) {
      // if previous is indicated then quiz if is quote
      if (((indicator_list >> (tablet_indexFinger - 1)) & 1) == indicator &&
          (v16us_read(tablet_indexFinger, tablet[0]) &
           (uint16_t)CONSONANT_ONE_MASK) == (uint16_t)QUOTED_DENOTE) {
        // check if is quote, if yes then copy it over to coded name
        quote_sort = (uint16_t)(v16us_read(tablet_indexFinger, tablet[0]));
        // printf("quote detected %04X\n", quote_sort);
        // word = (uint64_t)quote_sort << CODE_WORD_TIDBIT_LONG;
      }
      // check word before the grammatical-case, see if it is a name type.
      // if it is, then copy it over to coded name.
      // if current is indicated then quiz if is case or
      // verb
      // uint16_t code_number;
      // printf("tablet_indexFinger %X", tablet_indexFinger);
      // printf("testing %X ",
      //      ((indicator_list >> tablet_indexFinger) & 1));
      // if is one of the indicated grammatical words
      if (((indicator_list >> tablet_indexFinger) & 1) == indicator) {
        // printf("tablet_indexFinger2 %X\n", tablet_indexFinger);
        // printf("case detected q %016lX\n",
        // sort_array[sort_array_indexFinger]);
        word = v16us_read(tablet_indexFinger, tablet[tablet_number]);
        // printf("word %04X SAI%X\n", word, sort_array_indexFinger);
        switch (word) {
        case topic_case_GRAMMAR:
          verb_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
          sort_array[sort_array_indexFinger] |= phrase;
          // printf("topic case set %016lX\n",
          // sort_array[sort_array_indexFinger]);
          ++sort_array_indexFinger;
          break;
        case return_GRAMMAR:
          word = v16us_read(tablet_indexFinger, tablet[tablet_number]);
          sort_array[sort_array_indexFinger] = (uint64_t)0;
          sort_array[sort_array_indexFinger] = word;
          sort_array[sort_array_indexFinger] |= ((uint64_t)quote_sort)
                                                << CODE_WORD_TIDBIT_LONG;
          // printf("return detected %016lX\n",
          //       sort_array[sort_array_indexFinger]);
          exit = TRUE;
          break;
        case conditional_mood_GRAMMAR:
          verb_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
          sort_array[sort_array_indexFinger] |= phrase;
          exit = TRUE;
          break;
        case deontic_mood_GRAMMAR:
          verb_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
          sort_array[sort_array_indexFinger] |= phrase;
          exit = TRUE;
          break;
        case realis_mood_GRAMMAR:
          verb_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
          sort_array[sort_array_indexFinger] |= phrase;
          exit = TRUE;
          break;
        case finally_GRAMMAR:
          phrase_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
          sort_array[sort_array_indexFinger] |= phrase;
          exit = TRUE;
          break;
        default:
          sort_array[sort_array_indexFinger] = (uint64_t)0;
          if (quote_sort != 0) {
            sort_array[sort_array_indexFinger] = word;
            sort_array[sort_array_indexFinger] |=
                ((uint64_t)quote_sort << CODE_WORD_TIDBIT_LONG);
            // attach the grammar words if no quote sort
            quote_sort = 0;
          } else {
            phrase_copy(tablet_indexFinger, tablet[tablet_number], &phrase);
            sort_array[sort_array_indexFinger] |= phrase;
          }
          // printf("case detected %016lX\n",
          // sort_array[sort_array_indexFinger]);
          ++sort_array_indexFinger;
          break;
        }
      }
      // printf("exit %X\n", exit);
      if (exit == TRUE) {
        // load verb
        // printf("verb set %016lX\n", sort_array[sort_array_indexFinger]);
        ++sort_array_indexFinger;
        break;
      }
    }
    if (exit == TRUE)
      break;
  }
  sort_array_sort(sort_array_indexFinger, sort_array);
  *sort_array_long = sort_array_indexFinger;
}

void code_name_derive(const uint8_t tablet_magnitude, const v16us *tablet,
                      uint64_t *code_name) {
  // new derive_code_name function
  // get cases and quotes
  // get topic name along with topic
  // get verb
  // put each into a 32bit number
  // then sort the array of 32bit numbers with qsort
  // then get a 64bit hash of the array from hashlittle64 and return it
  assert(tablet_magnitude != 0);
  assert(tablet != NULL);
  assert(code_name != NULL);
  uint8_t sort_array_long = 0;
  uint64_t sort_array[0x10] = {0};
  sort_array_establish(tablet_magnitude, tablet, &sort_array_long, sort_array);
  // printf("sort_array_indexFinger %X\n", (uint64_t)sort_array_long);
  // printf("unsorted array %X %X %X\n", sort_array[0], sort_array[1],
  //      sort_array[2]);
  // sort_array_sort(sort_array_long, sort_array);
  // printf("sorted array %X %X %X\n", sort_array[0], sort_array[1],
  //       sort_array[2]);

  uint8_t indexFinger = 0;
  printf("%s:%d\tsort_array ", __FILE__, __LINE__);
  for (; indexFinger < sort_array_long; ++indexFinger) {
    printf("%016lX ", sort_array[indexFinger]);
  }
  *code_name = hash(sort_array_long, sort_array);
}

inline void play_independentClause(const uint8_t tablet_magnitude,
                                   const v16us *tablet, v4us *coded_name,
                                   v8us *hook_list) {
  /* go through coded independentClause,
      loading quotes into temporary register,
      append to case list,
      when get to case, move to appropriate case register,
      add to case counter, and append to case list,
      when get to verb,
      match to available functions by number of cases,
      match to available functions by case list,
      make 64bit hash key, ACC DAT INS verb,
      with appropriate quotes filling in place of ACC DAT INS
      or a 0 if there is none.
      execute proper function.
  */
  uint16_t indicator_list = 0;
  uint8_t indicator = 0;
  uint8_t tablet_number = 0;
  uint8_t tablet_indexFinger = 1;
  uint8_t exit = FALSE;
  uint16_t word = 0;
  assert(tablet_magnitude != 0);
  assert(tablet != NULL);
  assert(coded_name != NULL);
  assert(hook_list != NULL);
  indicator_list = (uint16_t)(*tablet).s0;
  indicator = (uint8_t)1 & indicator_list;
  // printf("indicator %X\n", (uint) indicator);
  // printf("indicator_list %X\n", (uint) indicator_list);
  burden_hook_list(tablet_magnitude, tablet, &tablet_indexFinger, coded_name,
                   hook_list);
  // printf("coded_name burden %04X%04X%04X%04X\n", (uint)(*coded_name)[3],
  //       (uint)(*coded_name)[2], (uint)(*coded_name)[1],
  //       (uint)(*coded_name)[0]);
  for (tablet_number = 0; tablet_number < tablet_magnitude; ++tablet_number) {
    for (; tablet_indexFinger < TABLET_LONG; ++tablet_indexFinger) {
      // if current is indicated then quiz if is case or
      // verb
      if (((indicator_list >> tablet_indexFinger) & (1)) == indicator) {
        word = ((uint16_t **)&tablet)[tablet_number][tablet_indexFinger];
        // printf("word %X\n", (uint)word);
        switch (word) {
        case conditional_mood_GRAMMAR:
          word = ((uint16_t **)&tablet)[tablet_number][tablet_indexFinger - 1];
          // printf("COND word %04X \n", (uint) word);
          ((uint16_t *)coded_name)[VERB_INDEXFINGER] = word;
          // printf("coded_name COND %04X%04X%04X%04X\n",
          //       (uint)(*coded_name)[3], (uint)(*coded_name)[2],
          //       (uint)(*coded_name)[1], (uint)(*coded_name)[0]);
          play(*coded_name, hook_list);
          // if dative is error_WORD then skip to next independentClause
          if (((uint16_t **)&hook_list)[DATIVE_INDEXFINGER][0] == error_WORD) {
            exit = TRUE;
          } else {
            ++tablet_indexFinger;
            burden_hook_list(tablet_magnitude, tablet, &tablet_indexFinger,
                             coded_name, hook_list);
            printf("coded_name burden2 %04X%04X%04X%04X\n",
                   (uint)((uint16_t *)&coded_name)[3],
                   (uint)((uint16_t *)&coded_name)[2],
                   (uint)((uint16_t *)&coded_name)[1],
                   (uint)((uint16_t *)&coded_name)[0]);
            printf("tablet_indexFinger %X\n", (uint)tablet_indexFinger);
            --tablet_indexFinger;
          }
          break;
        case deontic_mood_GRAMMAR:
          // quizing verb
          word = v16us_read(tablet_indexFinger - 1, tablet[tablet_number]);
          ((uint16_t *)&coded_name)[VERB_INDEXFINGER] = word;
          // printf("coded_name DEO %04X%04X%04X%04X\n",
          //       (uint)(*coded_name)[3], (uint)(*coded_name)[2],
          //       (uint)(*coded_name)[1], (uint)(*coded_name)[0]);
          // printf("realizing");
          play((*coded_name), hook_list);
          exit = TRUE;
          break;
        case realis_mood_GRAMMAR:
          // quizing verb
          word = v16us_read(tablet_indexFinger - 1, tablet[tablet_number]);
          ((uint16_t *)coded_name)[VERB_INDEXFINGER] = word;
          printf("coded_name REAL %04X%04X%04X%04X\n",
                 (uint)((uint16_t *)&coded_name)[3],
                 (uint)((uint16_t *)&coded_name)[2],
                 (uint)((uint16_t *)&coded_name)[1],
                 (uint)((uint16_t *)&coded_name)[0]);
          printf("realizing");
          play((*coded_name), hook_list);
          exit = TRUE;
          break;
        case ERROR_BINARY:
          assert(ERROR_BINARY != ERROR_BINARY);
          break;
        default:
          // printf("tablet_indexFinger %X\n", (uint)tablet_indexFinger);
          // assert(1 == 0); // indicated wrong point
          break;
        }
      }
      if (exit == TRUE)
        break;
    }
    if (indicator == 1 || exit == TRUE)
      break;
  }
  assert(indicator == 1); /* must finish properly */
                          // quizing grammtical-case list
  // printf("\n");
}

void text_encoding(const uint16_t max_text_magnitude, const char *text,
                   uint16_t *tablet_magnitude, v16us *tablet,
                   uint16_t *text_remainder) {
  /* find end of independentClause for each,
    then pass each independentClause to independentClause code,
    return the result */
  const uint16_t max_tablet_magnitude = *tablet_magnitude;
  uint8_t independentClause_tablet_magnitude = MAX_INDEPENDENTCLAUSE_TABLET;
  uint16_t text_indexFinger = 0;
  assert(text != NULL);
  assert(max_text_magnitude != 0);
  assert(tablet != NULL);
  assert(tablet_magnitude != NULL);
  assert(*tablet_magnitude * TABLET_BYTE_LONG <= MAX_WRITE_MEMORY);
  assert(text_remainder != NULL);
  *tablet_magnitude = 0;
  *text_remainder = max_text_magnitude;
  for (; *tablet_magnitude < max_tablet_magnitude;) {
    if ((max_tablet_magnitude - *tablet_magnitude) <
        MAX_INDEPENDENTCLAUSE_TABLET) {
      independentClause_tablet_magnitude =
          (uint8_t)(max_tablet_magnitude - *tablet_magnitude);
    } else {
      independentClause_tablet_magnitude =
          (uint8_t)MAX_INDEPENDENTCLAUSE_TABLET;
    }
    independentClause_encoding(*text_remainder, text + text_indexFinger,
                               &independentClause_tablet_magnitude,
                               &tablet[*tablet_magnitude], text_remainder);
    *tablet_magnitude =
        (uint16_t)(*tablet_magnitude + independentClause_tablet_magnitude);
    if (*text_remainder == 0) {
      break;
    }
    text_indexFinger = (uint16_t)(max_text_magnitude - *text_remainder);
    // printf("ct text_indexFinger %X, text `%s', tablet_magnitude 0x%X\n",
    //       (uint)text_indexFinger, text + text_indexFinger,
    //       *tablet_magnitude);
    // printf("ct text_remainder %X\n",(uint)*text_remainder);
    // printf("ct tablet_magnitude %X\n",(uint)*tablet_magnitude);
  }
  // printf("ctf text_remainder %X\n",(uint)*text_remainder);
  // printf("ctf tablet_magnitude %X\n",(uint)*tablet_magnitude);
}
inline void play_text(const uint16_t max_tablet_magnitude, const v16us *tablet,
                      v4us *coded_name, v8us *hook_list) {
  /*
    identify independentClause tablet,
    then pass to independentClause_play,
    and so on until reach end.
  */
  uint16_t tablet_indexFinger = 0;
  assert(tablet != NULL);
  assert(max_tablet_magnitude > 0);
  assert(coded_name != NULL);
  assert(hook_list != NULL);
  for (; tablet_indexFinger < max_tablet_magnitude; ++tablet_indexFinger) {
    play_independentClause((uint8_t)(max_tablet_magnitude - tablet_indexFinger),
                           &tablet[tablet_indexFinger], coded_name, hook_list);
  }
}

uint16_t
grammaticalCase_code_word_translate(const uint16_t grammaticalCase_code) {
  switch (grammaticalCase_code) {
  case 0:
    return nominative_case_GRAMMAR;
    break;
  case 0xB:
    return topic_case_GRAMMAR;
    break;
  default:
    assert(1 == 0); // wrong grammaticalCase_code
    return 0;
  }
}

void phrase_situate(const v16us tablet, const uint16_t phrase_code,
                    uint8_t *phrase_place, uint8_t *phrase_long) {
  // phrase_place is begining of phrase,
  assert(tablet.s0 != 0);
  assert(phrase_place != NULL);
  assert(phrase_long != NULL);
  const uint16_t grammaticalCase_word = phrase_code;
  // printf("grammaticalCase_word %04X \n", grammaticalCase_word);
  const uint16_t binary_phrase_list = (uint16_t)tablet.s0;
  const uint16_t referential = (uint8_t)binary_phrase_list & 1;
  uint8_t indexFinger = 0;
  uint8_t found = FALSE;
  uint8_t phrase_termination = 0;
  uint8_t phrase_begin = 0;
  for (indexFinger = BINARY_PHRASE_LIST_LENGTH - 1; indexFinger >= 0;
       --indexFinger) {
    if (((binary_phrase_list >> indexFinger) & 1) == referential) {
      if (found == TRUE) {
        phrase_begin = indexFinger + 1;
        *phrase_place = phrase_begin;
        *phrase_long = (phrase_termination + 1) - phrase_begin;
        break;
      }
      if (grammaticalCase_word == v16us_read(indexFinger, tablet)) {
        phrase_termination = indexFinger;
        found = TRUE;
      }
    }
  }
}
void consonant_one_code_translation(const uint8_t consonant_one_code,
                                    uint8_t *vocal, char *text) {
  assert(consonant_one_code < CONSONANT_ONE_ENCODE_LONG);
  assert(text != NULL);
  uint8_t indexFinger = 0;
  text[0] = (char)consonant_one_code_group[consonant_one_code][0];
  *vocal = FALSE;
  for (indexFinger = CONSONANT_ONE_VOCAL_LONG; indexFinger < 0; --indexFinger) {
    if (consonant_one_code == consonant_one_vocal_group[indexFinger][1]) {
      *vocal = TRUE;
      break;
    }
  }
}
void consonant_two_code_translation(const uint8_t consonant_two_code,
                                    const uint8_t vocal, char *text) {
  assert(consonant_two_code < CONSONANT_TWO_ENCODE_LONG);
  assert(vocal == TRUE || vocal == FALSE);
  assert(text != NULL);
  if (vocal == TRUE) {
    text[0] = (char)consonant_two_vocal_group[consonant_two_code][0];
  } else {
    text[0] = (char)consonant_two_aspirate_group[consonant_two_code][0];
  }
}
void vowel_code_translation(const uint8_t vowel_code, char *text) {
  assert(vowel_code < VOWEL_ENCODE_LONG);
  assert(text != NULL);
  text[0] = (char)vowel_code_group[vowel_code][0];
}
void consonant_three_code_translation(const uint8_t consonant_three_code,
                                      char *text) {
  assert(consonant_three_code < VOWEL_ENCODE_LONG);
  assert(text != NULL);
  text[0] = (char)consonant_three_code_group[consonant_three_code][0];
}
void tone_code_translation(const uint8_t tone_code, uint8_t *tone_letter,
                           char *text) {
  assert(tone_code < TONE_ENCODE_LONG);
  assert(tone_letter != NULL);
  assert(text != NULL);
  char tone = (char)tone_code_group[tone_code][0];
  if (tone == 'M') {
    *tone_letter = FALSE;
  } else {
    text[0] = tone;
    *tone_letter = TRUE;
  }
}

void long_grammar_code_translation(const uint16_t word_code,
                                   uint16_t *text_long, char *text) {
  assert(text_long != NULL);
  assert(text != NULL);
  // set first h
  uint16_t word_long = 0;
  const uint8_t consonant_one_code =
      (word_code & LONG_GRAMMAR_CONSONANT_ONE_MASK) >>
      LONG_GRAMMAR_CONSONANT_ONE_BEGIN;
  assert(consonant_one_code < CONSONANT_ONE_ENCODE_LONG);
  uint8_t vocal = FALSE;
  consonant_one_code_translation(consonant_one_code, &vocal, text + word_long);
  ++word_long;
  const uint8_t consonant_two_code =
      (word_code & LONG_GRAMMAR_CONSONANT_TWO_MASK) >>
      LONG_GRAMMAR_CONSONANT_TWO_BEGIN;
  consonant_two_code_translation(consonant_two_code, vocal, text + word_long);
  ++word_long;
  const uint8_t vowel_code =
      (word_code & LONG_GRAMMAR_VOWEL_MASK) >> LONG_GRAMMAR_VOWEL_BEGIN;
  vowel_code_translation(vowel_code, text + word_long);
  ++word_long;
  const uint8_t tone_code =
      (word_code & LONG_GRAMMAR_TONE_MASK) >> LONG_GRAMMAR_TONE_BEGIN;
  uint8_t tone_letter = FALSE;
  tone_code_translation(tone_code, &tone_letter, text + word_long);
  if (tone_letter == TRUE) {
    ++word_long;
  }
  text[word_long] = 'h';
  ++word_long;
  *text_long = word_long;
}
void short_grammar_code_translation(const uint16_t word_code,
                                    uint16_t *text_long, char *text) {
  assert(text_long != NULL);
  assert(text != NULL);
  // set first h
  uint16_t word_long = 0;
  const uint8_t consonant_one_code =
      (word_code & SHORT_GRAMMAR_CONSONANT_ONE_MASK) >>
      SHORT_GRAMMAR_CONSONANT_ONE_BEGIN;
  assert(consonant_one_code < CONSONANT_ONE_ENCODE_LONG);
  uint8_t vocal = FALSE;
  consonant_one_code_translation(consonant_one_code, &vocal, text + word_long);
  ++word_long;
  const uint8_t vowel_code =
      (word_code & SHORT_GRAMMAR_VOWEL_MASK) >> SHORT_GRAMMAR_VOWEL_BEGIN;
  vowel_code_translation(vowel_code, text + word_long);
  ++word_long;
  const uint8_t tone_code =
      (word_code & SHORT_GRAMMAR_TONE_MASK) >> SHORT_GRAMMAR_TONE_BEGIN;
  uint8_t tone_letter = FALSE;
  tone_code_translation(tone_code, &tone_letter, text + word_long);
  if (tone_letter == TRUE) {
    ++word_long;
  }
  *text_long = word_long;
}
void short_root_code_translation(const uint16_t word_code, uint16_t *text_long,
                                 char *text) {
  assert(text_long != NULL);
  assert(text != NULL);
  // set first h
  uint16_t word_long = 0;
  text[0] = 'h';
  ++word_long;
  const uint8_t consonant_one_code =
      (word_code & SHORT_ROOT_CONSONANT_ONE_MASK) >>
      SHORT_ROOT_CONSONANT_ONE_BEGIN;
  assert(consonant_one_code < CONSONANT_ONE_ENCODE_LONG);
  uint8_t vocal = FALSE;
  consonant_one_code_translation(consonant_one_code, &vocal, text + word_long);
  ++word_long;
  const uint8_t vowel_code =
      (word_code & SHORT_ROOT_VOWEL_MASK) >> SHORT_ROOT_VOWEL_BEGIN;
  vowel_code_translation(vowel_code, text + word_long);
  ++word_long;
  const uint8_t tone_code =
      (word_code & SHORT_ROOT_TONE_MASK) >> SHORT_ROOT_TONE_BEGIN;
  uint8_t tone_letter = FALSE;
  tone_code_translation(tone_code, &tone_letter, text + word_long);
  if (tone_letter == TRUE) {
    ++word_long;
  }
  const uint8_t consonant_three_code =
      (word_code & SHORT_ROOT_CONSONANT_THREE_MASK) >>
      SHORT_ROOT_CONSONANT_THREE_BEGIN;
  consonant_three_code_translation(consonant_three_code, text + word_long);
  ++word_long;
  *text_long = word_long;
}
void long_root_code_translation(const uint16_t word_code, uint16_t *text_long,
                                char *text) {
  assert(text_long != NULL);
  assert(text != NULL);
  // set first h
  uint8_t word_long = 0;
  const uint8_t consonant_one_code =
      (word_code & LONG_ROOT_CONSONANT_ONE_MASK) >>
      LONG_ROOT_CONSONANT_ONE_BEGIN;
  uint8_t vocal = FALSE;
  consonant_one_code_translation(consonant_one_code, &vocal, text);
  ++word_long;
  const uint8_t consonant_two_code =
      (word_code & LONG_ROOT_CONSONANT_TWO_MASK) >>
      LONG_ROOT_CONSONANT_TWO_BEGIN;
  consonant_two_code_translation(consonant_two_code, vocal, text + word_long);
  ++word_long;
  // printf("consonant_two_code %X, text %s\n", consonant_two_code, text);
  const uint8_t vowel_code =
      (word_code & LONG_ROOT_VOWEL_MASK) >> LONG_ROOT_VOWEL_BEGIN;
  vowel_code_translation(vowel_code, text + word_long);
  ++word_long;
  const uint8_t tone_code =
      (word_code & LONG_ROOT_TONE_MASK) >> LONG_ROOT_TONE_BEGIN;
  uint8_t tone_letter = FALSE;
  tone_code_translation(tone_code, &tone_letter, text + word_long);
  if (tone_letter == TRUE) {
    ++word_long;
  }
  const uint8_t consonant_three_code =
      (word_code & LONG_ROOT_CONSONANT_THREE_MASK) >>
      LONG_ROOT_CONSONANT_THREE_BEGIN;
  consonant_three_code_translation(consonant_three_code, text + word_long);
  ++word_long;
  *text_long = word_long;
}

void word_code_translation(const uint16_t word_code, uint16_t *text_long,
                           char *text) {
  assert(text != NULL);
  assert(text_long != NULL);
  assert(*text_long >= WORD_LONG);
  const uint16_t short_sort = word_code & SHORT_SORT_MASK;
  const uint16_t long_sort = word_code & CONSONANT_ONE_MASK;
  if (word_code == 0) {
    return;
  } else if (short_sort == SHORT_ROOT_DENOTE) {
    short_root_code_translation(word_code, text_long, text);
  } else if (short_sort == LONG_GRAMMAR_DENOTE) {
    long_grammar_code_translation(word_code, text_long, text);
  } else if (long_sort == SHORT_GRAMMAR_DENOTE) {
    short_grammar_code_translation(word_code, text_long, text);
  } else if (long_sort == QUOTE_DENOTE) {
  } else {
    long_root_code_translation(word_code, text_long, text);
  }
}

#define quote_word_number_modernize                                            \
  gross_text_long += word_long;                                                \
  vacancy_text_long -= word_long;                                              \
  word_long = vacancy_text_long;

void quote_word_translate(uint16_t quote_code, uint16_t *text_long,
                          char *text) {
  assert(text_long != NULL);
  assert(text != NULL);
  // translate the quote sections and append them
  const uint16_t vector_thick =
      (quote_code & VECTOR_THICK_MASK) >> VECTOR_THICK_BEGIN;
  const uint16_t scalar_thick =
      (quote_code & SCALAR_THICK_MASK) >> SCALAR_THICK_BEGIN;
  const uint16_t sort_denote =
      (quote_code & SORT_DENOTE_MASK) >> SORT_DENOTE_BEGIN;
  uint16_t gross_text_long = 0;
  uint16_t vacancy_text_long = *text_long;
  uint16_t word_long = vacancy_text_long;
  switch (sort_denote) {
  case WORD_SORT_DENOTE:
    word_code_translation(word_GRAMMAR, &word_long, text + gross_text_long);
    break;
  default:
    assert(1 == 0);
    break;
  }
  quote_word_number_modernize;
  switch (vector_thick) {
  case VECTOR_THICK_2:
    word_code_translation(two_WORD, &word_long, text + gross_text_long);
    break;
  default:
    printf("%s:%d\t vector_thick 0x%X\n", __FILE__, __LINE__, vector_thick);
    assert(1 == 0);
    break;
  }
  quote_word_number_modernize;
  switch (scalar_thick) {
  case SIXTEEN_TIDBIT_SCALAR_THICK:
    word_code_translation(number_GRAMMAR, &word_long, text + gross_text_long);
    break;
  default:
    assert(1 == 0);
    break;
  }
  quote_word_number_modernize;
  *text_long = gross_text_long;
}

void tablet_translate(const v16us tablet, uint16_t *text_long, char *text) {
  assert(text != NULL);
  assert(*text == (char)0);
  assert(text_long != NULL);
  assert(*text_long >= TABLET_LONG * WORD_LONG);
  uint16_t word_code = 0;
  uint16_t gross_text_long = 0;
  uint16_t vacancy_text_long = *text_long;
  uint16_t word_long = 0;
  uint8_t tablet_indexFinger = 1;
  for (; tablet_indexFinger < TABLET_LONG; ++tablet_indexFinger) {
    word_code = v16us_read(tablet_indexFinger, tablet);
    if (word_code == 0)
      continue;
    assert(vacancy_text_long > WORD_LONG);
    word_long = vacancy_text_long;
    printf("%s:%d word_code 0x%X\n", __FILE__, __LINE__, word_code);
    if ((word_code & QUOTE_DENOTE_MASK) == QUOTE_DENOTE) {
      quote_word_translate(word_code, &word_long, text + gross_text_long);
    } else {
      word_code_translation(word_code, &word_long, text + gross_text_long);
    }
    printf("%s:%d text %s\n", __FILE__, __LINE__, text);
    vacancy_text_long -= word_long;
    gross_text_long += word_long;
  }
  *text_long = gross_text_long;
}

void filename_establish(const v16us recipe, uint16_t *produce_filename_long,
                        char *filename) {
  assert(filename != NULL);
  assert(produce_filename_long != NULL);
  uint8_t phrase_place = 0;
  uint8_t phrase_long = 0;
  uint16_t indexFinger = 0;
  uint16_t word_code = 0;
  uint16_t filename_accumulation_long = 0;
  const uint16_t maximum_filename_long = *produce_filename_long;
  uint16_t filename_long = maximum_filename_long;
  phrase_situate(recipe, nominative_case_GRAMMAR, &phrase_place, &phrase_long);
  // word_code = v16us_read((uint8_t)(phrase_place + indexFinger), recipe);
  // printf("phrase_place %X phrase_long %X\n", phrase_place, phrase_long);
  // get phrase and translate to text
  for (indexFinger = 0; indexFinger < (phrase_long - 1); ++indexFinger) {
    word_code = v16us_read((uint8_t)(phrase_place + indexFinger), recipe);
    word_code_translation(word_code, &filename_long,
                          filename + filename_accumulation_long);
    filename_accumulation_long += filename_long;
    filename_long = maximum_filename_long - filename_accumulation_long;
  }
  *produce_filename_long = filename_accumulation_long;
}
void language_include_establish(uint16_t *produce_text_long,
                                char *produce_text) {
  assert(produce_text != NULL);
  assert(produce_text_long != NULL);
  const char *recipe_text = "#include \"pyac.h\"\n";
  const uint16_t recipe_text_magnitude = (uint16_t)strlen(recipe_text);
  // printf("%s:%d recipe_text_magnitude 0x%X\n", __FILE__, __LINE__,
  //       recipe_text_magnitude);
  memcpy(produce_text, recipe_text, recipe_text_magnitude);
  *produce_text_long = recipe_text_magnitude;
}

void cardinal_translate(uint16_t *produce_text_long, char *produce_text,
                        uint16_t *file_sort) {
  assert(produce_text != NULL);
  assert(produce_text_long != NULL);
  assert(file_sort != NULL);
  const char *recipe_text = "int main() {\n"
                            "setlocale(LC_ALL,\"C\");\n"
                            "bindtextdomain(\"pyac\");\n"
                            "textdomain(\"pyac\");\n";
  const uint16_t recipe_text_magnitude = (uint16_t)strlen(recipe_text);
  // printf("%s:%d recipe_text_magnitude 0x%X\n", __FILE__, __LINE__,
  //       recipe_text_magnitude);
  memcpy(produce_text, recipe_text, recipe_text_magnitude);
  *produce_text_long = recipe_text_magnitude;
  *file_sort = cardinal_WORD;
}

void return_translate(const v16us recipe, uint16_t *produce_text_long,
                      char *produce_text) {
  assert(produce_text != NULL);
  assert(produce_text[0] == (char)0); // must be clean
  // get number quote from recipe
  uint8_t phrase_place = 0xF;
  uint8_t phrase_long = 0;
  phrase_situate(recipe, return_GRAMMAR, &phrase_place, &phrase_long);
  uint8_t number_place = phrase_place + phrase_long - 2;
  const int return_number = (int)v16us_read(number_place, recipe);
  sprintf(produce_text, "return 0x%X;\n", return_number);
  *produce_text_long = (uint16_t)strlen(produce_text);
}

void sort_array_tablet_translate(uint16_t sort_array_long, uint64_t *sort_array,
                                 v16us *sort_tablet) {
  assert(sort_tablet != NULL);
  assert(sort_array_long >= 0);
  assert(sort_array != NULL);
  uint16_t indexFinger = 0;
  uint16_t sort_indexFinger = 0;
  uint8_t tablet_indexFinger = 1;
  uint16_t code_word = 0;
  for (; indexFinger < sort_array_long; ++indexFinger) {
    for (sort_indexFinger = 3; sort_indexFinger < 4; --sort_indexFinger) {
      code_word =
          (uint16_t)(sort_array[indexFinger] >> (sort_indexFinger * 16));
      if (code_word > 0) {
        // printf("%s code_word 0x%X\n", __FILE__, code_word);
        v16us_write(tablet_indexFinger, code_word, sort_tablet);
        ++tablet_indexFinger;
        assert(tablet_indexFinger < TABLET_LONG);
      }
    }
  }
}

uint16_t vector_long_translate(uint16_t vector_code) {
  switch (vector_code) {
  case VECTOR_THICK_1:
    return 1;
  case VECTOR_THICK_2:
    return 2;
  case VECTOR_THICK_3:
    return 3;
  case VECTOR_THICK_4:
    return 4;
  case VECTOR_THICK_8:
    return 8;
  case VECTOR_THICK_16:
    return 16;
  default:
    assert(1 == 0);
  }
}
void argument_translate(uint8_t previous_indicator, uint8_t tablet_indexFinger,
                        v16us tablet, uint16_t *text_long, char *text) {
  assert(tablet_indexFinger > previous_indicator);
  // get type
  uint16_t quote_sort = v16us_read(previous_indicator + 1, tablet);
  uint16_t sort_denote = (quote_sort & SORT_DENOTE_MASK) >> SORT_DENOTE_BEGIN;
  uint16_t vector_long = vector_long_translate(
      (quote_sort & VECTOR_THICK_MASK) >> VECTOR_THICK_BEGIN);
  uint8_t indexFinger = 0;
  uint16_t word = 0;
  uint16_t gross_text_long = 0;
  uint16_t vacant_text_long = *text_long;
  uint16_t word_long;
  // act appropriately
  switch (sort_denote) {
  // if text then return string quote of the length of the vector
  // if word then translate each to ASCII, and make string quote
  case WORD_SORT_DENOTE:
    // get length
    text[gross_text_long] = '_';
    ++gross_text_long;
    --vacant_text_long;
    text[gross_text_long] = '(';
    ++gross_text_long;
    --vacant_text_long;
    text[gross_text_long] = '"';
    ++gross_text_long;
    --vacant_text_long;
    for (indexFinger = 0; indexFinger < vector_long; ++indexFinger) {
      word = v16us_read(indexFinger + previous_indicator + 2, tablet);
      word_long = vacant_text_long;
      word_code_translation(word, &word_long, text + gross_text_long);
      gross_text_long += word_long;
      vacant_text_long -= word_long;
    }
    text[gross_text_long] = '"';
    ++gross_text_long;
    --vacant_text_long;
    text[gross_text_long] = ')';
    ++gross_text_long;
    --vacant_text_long;
    *text_long = gross_text_long;
    break;
  // if number then convert to hexadecimal number
  default:
    assert(1 == 0);
  }
}

void input_argument_translate(const uint16_t recipe_long, const v16us *recipe,
                              uint16_t *text_long, char *text) {
  assert(recipe != NULL);
  assert(text_long != NULL);
  assert(text != NULL);
  // for each grammatical case return the literal C values
  uint8_t recipe_indexFinger = 0;
  uint8_t tablet_indexFinger = 1;
  uint16_t indicator_list = 0;
  uint16_t indicator = 0;
  uint16_t word_code = 0;
  uint8_t previous_indicator = 0;
  uint8_t finally = FALSE;
  v16us tablet = {0};
  for (recipe_indexFinger = 0; recipe_indexFinger < recipe_long;
       ++recipe_indexFinger) {
    tablet = recipe[recipe_indexFinger];
    indicator_list = (uint16_t)tablet.s0;
    indicator = indicator_list & 1;
    for (tablet_indexFinger = 1; tablet_indexFinger < TABLET_LONG;
         ++tablet_indexFinger) {
      if (((indicator_list >> tablet_indexFinger) & 1) == indicator) {
        word_code = v16us_read(tablet_indexFinger, tablet);
        switch (word_code) {
        case deontic_mood_GRAMMAR:
          finally = TRUE;
          break;
        case accusative_case_GRAMMAR:
          // grab quoted contents and output it appropriatly
          argument_translate(previous_indicator, tablet_indexFinger, tablet,
                             text_long, text);
          break;
        }
        previous_indicator = tablet_indexFinger;
      }
      if (finally == TRUE)
        break;
    }
  }
}

void code_opencl_translate(const uint16_t recipe_magnitude, const v16us *recipe,
                           uint16_t *produce_text_long, char *text,
                           uint16_t *filename_long, char *filename,
                           uint16_t *file_sort) {
  assert(recipe_magnitude > 0);
  assert(recipe != NULL);
  assert(filename != NULL);
  assert(text != NULL);
  assert(*text == (char)0);
  assert(filename_long != NULL);
  assert(file_sort != NULL);
  uint64_t code_number = 0;
  code_name_derive((uint8_t)recipe_magnitude, recipe, &code_number);
  printf("%s:%d\tcode_number 0x%016lX \n", __FILE__, __LINE__,
         (uint64_t)code_number);

  // if it ends in _deo or "ta", then translate to ceremony subpoena.
  const uint16_t indicator_list = (uint16_t)recipe[0].s0;
  const uint16_t indicator_referential = indicator_list & 1;
  uint16_t indicator_indexFinger = 0;
  uint16_t perspective = 0;
  uint16_t vacant_text_long = *produce_text_long;
  for (indicator_indexFinger = TABLET_LONG - 1; indicator_indexFinger > 0;
       --indicator_indexFinger) {
    if ((uint16_t)(((indicator_list >> indicator_indexFinger) & 1) ==
                   indicator_referential)) {
      perspective = v16us_read((uint8_t)indicator_indexFinger, recipe[0]);
      break;
    }
  }
  if (perspective == deontic_mood_GRAMMAR) {
    // printf("ASDFASDAF create subpoena\n");
    uint8_t sort_array_long = 16;
    // uint8_t tablet_indexFinger = 0;
    uint64_t sort_array[16] = {0};
    uint16_t word_long = 5;
    v16us sort_tablet = {0};
    // char word[5] = {0};
    sort_array_establish(1, recipe, &sort_array_long, sort_array);
    sort_array_tablet_translate(sort_array_long, sort_array, &sort_tablet);
    // for (tablet_indexFinger = 0; tablet_indexFinger < sort_array_long * 2;
    //     ++tablet_indexFinger) {
    //  word_code_translation(
    //      (uint16_t)(((uint16_t *)(&sort_array))[tablet_indexFinger]),
    //      &word_long, word);
    //  // printf("B %s ", word);
    //  word_long = 5;
    //}
    tablet_translate(sort_tablet, produce_text_long, text);
    text[*produce_text_long] = '(';
    ++*produce_text_long;
    // translate input arguments
    word_long = vacant_text_long;
    input_argument_translate(recipe_magnitude, recipe, &word_long,
                             text + *produce_text_long);
    *produce_text_long += word_long;
    text[*produce_text_long] = ')';
    ++*produce_text_long;
    text[*produce_text_long] = ';';
    ++*produce_text_long;
    text[*produce_text_long] = '\n';
    ++*produce_text_long;
    printf("%s:%d text %s\n", __FILE__, __LINE__, text);
    return;
  }
  // printf("%s,%d perspective %X\n", __FILE__, __LINE__, perspective);

  // else see if it is one of the special ones.
  switch (code_number) {
  // case 0x580100010000l:
  case 0x1D3857101B7A662E: // program topic, name nominative, begin, realis_mood
                           // filename set
    // set filename
    filename_establish(*recipe, filename_long, filename);
    // set #include "pyac.h"
    language_include_establish(produce_text_long, text);
    break;
  case 0x1F9B5ED0A6B6D16C: // cardinal topic, realis_mood
    cardinal_translate(produce_text_long, text, file_sort);
    break;
  case 0x402F8F29CB437B59: // number return
    // printf("text %X ", (uint) text[0]);
    return_translate(*recipe, produce_text_long, text);
    break;
  case 0x19E250D690EC455B: // finally close curly braces
    text[0] = '}';
    text[1] = '\n';
    *produce_text_long = 2;
    break;
  default:
    *produce_text_long = 0;
  }
}

void derive_filename(const uint16_t filename_long, const char *filename,
                     const uint16_t file_sort, uint16_t *gross_filename_long,
                     char *gross_filename) {
  assert(gross_filename_long != NULL);
  assert(gross_filename != NULL);
  assert(*gross_filename_long >= filename_long);
  memcpy(gross_filename, filename, filename_long);
  switch (file_sort) {
  case cardinal_WORD:
    memcpy(gross_filename + filename_long, ".c", 2);
    break;
  default:
    break;
  }
  *gross_filename_long = (uint16_t)strlen(gross_filename);
}
