#ifndef PARSER_H
#define PARSER_H
#include "sort.h"

#define CONSONANT_ONE_THICK 5
#define CONSONANT_ONE_MASK 0x1F
#define CONSONANT_ONE_ENCODE_LONG 32
#define CONSONANT_ONE_VOCAL_LONG 3
#define CONSONANT_TWO_ENCODE_LONG 11
#define CONSONANT_TWO_VOCAL_LONG 8
#define CONSONANT_TWO_ASPIRATE_LONG 8
#define VOWEL_ENCODE_LONG 8
#define TONE_ENCODE_LONG 4
#define CONSONANT_THREE_ENCODE_LONG 8


const uint8_t consonant_one_code_group[CONSONANT_ONE_ENCODE_LONG][2];
const uint8_t consonant_one_vocal_group[CONSONANT_ONE_VOCAL_LONG][2];
const uint8_t consonant_two_code_group[CONSONANT_TWO_ENCODE_LONG][2];
const uint8_t vowel_code_group[VOWEL_ENCODE_LONG][2];
const uint8_t tone_code_group[TONE_ENCODE_LONG][2];
const uint8_t consonant_three_code_group[CONSONANT_THREE_ENCODE_LONG][2];
const uint8_t consonant_two_vocal_group[CONSONANT_TWO_VOCAL_LONG][2];
const uint8_t consonant_two_aspirate_group[CONSONANT_TWO_ASPIRATE_LONG][2];


extern  uint8_t vowel_Q(const char glyph);
extern  uint8_t tone_Q(const char glyph);

extern  uint8_t consonant_Q(const char glyph);

void first_word_derive(const uint16_t text_long, const char *ACC_text,
                       uint8_t *word_long, uint16_t *word_begin);

#endif
