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
#define NEWSPAPER_LONG 0x10

#define REALIS_MOOD 0x017E                     // li
#define DEONTIC_MOOD 0x095E                    // tu
#define CONDITIONAL_MOOD 0x9BE                 // cu
#define COUNTERFACTUAL_CONDITIONAL_MOOD 0x159E // f6
#define ACCUSATIVE_CASE 0x45E                  // ka
#define DATIVE_CASE 0x007E                     // yi
#define INSTRUMENTAL_CASE 0x087E               // yu

#define TRUTH_WORD 0x6109 // syan
#define LIE_WORD 0x600D   // cyin
#define ERROR_WORD 0xE4CD // croc

#define QUOTED_REFERENTIAL 0x1D
#define CONSONANT_ONE_MASK 0x1F
#define CONSONANT_ONE_THICK 5 // bits
#define UNSIGNED_CHAR_QUOTED 0x009D
#define SIGNED_CHAR_QUOTED 0x029D
#define SHORT_NUMBER_QUOTED 0x143D
#define QUOTED_LITERAL_INDEXFINGER 8

#define HOOK_LIST_LONG 3
#define VERB_INDEXFINGER 3
#define ACCUSATIVE_INDEXFINGER 2
#define INSTRUMENTAL_INDEXFINGER 1
#define DATIVE_INDEXFINGER 0

#define ERROR_BINARY 0
#define TABLET_LONG 0x10
#define WORD_THICK 2
#define V8US_LONG 16
#define TRUE 1
#define FALSE 0

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef ushort4 v4us;
typedef ushort8 v8us;
typedef ushort16 v16us;

int comparison_randomAccessMemory(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  while (n--)
    if (*p1 != *p2)
      return *p1 - *p2;
    else
      p1++, p2++;
  return 0;
}

void *copy_randomAccessMemory(void *dest, const void *src, size_t n) {
  char *dp = dest;
  const char *sp = src;
  while (n--)
    *dp++ = *sp++;
  return dest;
}

void agree(const int c, const v16us error_news,
           local uint8_t *newspaper_indexFinger, global v16us *newspaper) {
  uint8_t program_indexFinger = get_global_id(0);
  if (*newspaper_indexFinger < NEWSPAPER_LONG) {
    if (!c) {
      if (program_indexFinger < NEWSPAPER_LONG) {
        newspaper[program_indexFinger] = error_news;
      } else {
        newspaper[*newspaper_indexFinger] = error_news;
      }
      *newspaper_indexFinger += 1;
    }
  }
}

uint64_t splitMix64(local uint64_t *seed) {
  uint64_t z = (*seed += 0x9E3779B97F4A7C15);
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
  return z ^ (z >> 31);
}

inline void x6048009D00000000(unsigned char *text) {
  // agree(text != NULL);
  // printf("ini %02X\n", (uint)text[0]);
  // printf("%s", text);
}
inline void x6048029D00000000(signed char *text) {
  // agree(text != NULL);
  // printf("%s", text);
}
inline void x4124000000000000(v8us *hook_list) {
  if (comparison_randomAccessMemory(
          (char *)&hook_list[ACCUSATIVE_INDEXFINGER],
          (char *)&hook_list[INSTRUMENTAL_INDEXFINGER], 16) == 0) {
    ((uint16_t **)&hook_list)[DATIVE_INDEXFINGER][0] = TRUTH_WORD;
  } else {
    ((uint16_t **)&hook_list)[DATIVE_INDEXFINGER][0] = LIE_WORD;
  }
}
inline void x8006000000000000(v8us *hook_list) {
  if (comparison_randomAccessMemory(
          (char *)&hook_list[ACCUSATIVE_INDEXFINGER],
          (char *)&hook_list[INSTRUMENTAL_INDEXFINGER], 16) != 0) {
    ((uint16_t **)&hook_list)[DATIVE_INDEXFINGER][0] = TRUTH_WORD;
  } else {
    ((uint16_t **)&hook_list)[DATIVE_INDEXFINGER][0] = LIE_WORD;
  }
}

inline void xA130143D143D0000(uint16_t *accusative, uint16_t *instrumental) {
  if (*instrumental) {
    *accusative = (uint16_t) ~(*accusative);
  }
}
inline void xC450143D143D0000(uint16_t *accusative, uint16_t *instrumental) {
  *accusative = (uint16_t)(*accusative - *instrumental);
}
inline void x8006143D143D0000(uint16_t *accusative, uint16_t *instrumental) {
  *accusative = (uint16_t)(*accusative + *instrumental);
}

uint64_t roll_u64(const uint64_t random_seed, const uint8_t amount) {
  return (uint64_t)((random_seed >> amount) | (random_seed << (64 - amount)));
}

int isPowerOfTwo(unsigned int x) { return ((x != 0) && !(x & (x - 1))); }

void composition_program(const uint8_t activity_atom_long,
                         constant const v16us *restrict activity_atom,
                         const uint16_t program_long,
                         const uint64_t random_seed,
                         local uint64_t *random_workplace,
                         global v16us *restrict program,
                         local uint8_t *newspaper_indexFinger,
                         global v16us *newspaper) {
  /*algorithm:
      select a random element,
      add it to the program.*/
  uint8_t program_indexFinger = get_global_id(0);
  uint8_t random_indexFinger = 0;
  uint8_t tidbit_pluralNumber =
      (uint8_t)log2((float)(activity_atom_long - 1)) + 1;
  uint8_t tidbit_mask =
      (uint8_t)(pow((float)2, (float)tidbit_pluralNumber) - 1);
  uint8_t nomination;
  // agree(isPowerOfTwo(activity_atom_long),
  //      (v16us){0x1, 0xA42A, 0x1C6, 0x61AA, 0x4DE, 0xA20A, 0x15E, 0x2830,
  //              0x10DE, 0x83E, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  //      newspaper_indexFinger, newspaper);
  // agree(1 == 0, (v16us){0x41, 0xA152, 0x6082, 0x4DE, 0x22, 0x6050, 0x17E,
  // 0x0,
  //                      0x0, 0x0, 0x0, program_indexFinger, 0x0, 0x0, 0x0,
  //                      0x0},
  //      newspaper_indexFinger, newspaper);
  // agree(activity_atom_long > 0);
  // agree(activity_atom != NULL);
  // agree(program_long > 0);
  // agree(program != NULL);
  // agree(random_seed != 0);
  uint8_t random_nomination = 0xFF;
  uint8_t random_number =
      roll_u64(random_seed, tidbit_pluralNumber * program_indexFinger);
  nomination = (uint8_t)(random_number & tidbit_mask);
  if (nomination >= activity_atom_long) { // attempt to get fitting number
    *random_workplace =
        roll_u64(random_seed, tidbit_pluralNumber * program_indexFinger);
    for (random_indexFinger = 0; random_indexFinger < activity_atom_long;
         ++random_indexFinger) {
      if (nomination >= activity_atom_long) {
        nomination =
            (uint8_t)(roll_u64(splitMix64(random_workplace),
                               tidbit_pluralNumber * program_indexFinger) &
                      tidbit_mask);
      } else {
        break;
      }
    }
    random_nomination = nomination;
  }
  if (nomination >= activity_atom_long) {
    nomination -= activity_atom_long;
  }
  agree(1 == 0, (v16us){0x5, 0x6442, 0x470, 0x4DE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                        tidbit_pluralNumber, program_indexFinger,
                        random_nomination, (uint16_t)nomination,
                        (uint16_t)random_number, (uint16_t)*random_workplace},
        newspaper_indexFinger, newspaper);
  *program = activity_atom[nomination];
}

kernel void composition_population(
    const uint8_t activity_atom_long,
    constant const v16us *restrict activity_atom, const uint16_t program_long,
    const uint8_t population_long, const uint64_t random_seed,
    local uint64_t *random_workplace, global v16us *restrict population,
    local uint8_t *newspaper_indexFinger, global v16us *newspaper) {
  uint8_t program_indexFinger = get_global_id(0);
  // v16us news = 1;
  if (program_indexFinger < population_long) {
    agree(1 == 0,
          (v16us){0x41, 0xA152, 0x6082, 0x4DE, 0x22, 0x6050, 0x17E, 0x0, 0x0,
                  0x0, 0x0, program_indexFinger,
                  (uint16_t)roll_u64(random_seed, 8 * program_indexFinger), 0x0,
                  0x0, 0x0},
          newspaper_indexFinger, newspaper);
    composition_program(activity_atom_long, activity_atom, program_long,
                        random_seed, random_workplace,
                        &population[program_indexFinger], newspaper_indexFinger,
                        newspaper);
  }
}
