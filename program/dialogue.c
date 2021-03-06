#include "dialogue.h"
#include <assert.h>
#include <locale.h>
#include <string.h>

void paper_read(const char *file_name, const size_t paper_number,
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

void paper_write(const char *file_name, const size_t paper_number,
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
// void paper_read(const char *file_name, const size_t paper_number,
//                       uint16_t *paper_size, char *paper_storage) {
//  FILE *file_spot = NULL;
//  int answer = 0;
//  uint16_t text_spot = 0;
//  uint16_t size = 0;
//  int glyph = (char)0;
//  assert(file_name != 0);
//  assert(strlen(file_name) > 0);
//  assert(paper_storage != NULL);
//  assert(*paper_size >= MAXIMUM_PAPER_LONG);
//  file_spot = fopen(file_name, "r");
//  assert(file_spot != NULL);
//  if (file_spot != NULL) {
//    answer = fseek(file_spot, (int)paper_number * MAXIMUM_PAPER_LONG,
//    SEEK_SET);
//    // assert(answer == 0);
//    if (answer == 0) {
//      size = (uint16_t)(fread(paper_storage, MAXIMUM_PAPER_LONG, 1,
//      file_spot));
//      if (size != 0) {
//        size = (uint16_t)(size * MAXIMUM_PAPER_LONG);
//      } else {
//        answer =
//            fseek(file_spot, (int)paper_number * MAXIMUM_PAPER_LONG,
//            SEEK_SET);
//        assert(answer == 0);
//        for (text_spot = 0; text_spot < MAXIMUM_PAPER_LONG; ++text_spot) {
//          glyph = fgetc(file_spot);
//          if (glyph == EOF)
//            break;
//          paper_storage[text_spot] = (char)glyph;
//          ++size;
//        }
//      }
//      // printf("%X size \n", (uint) size);
//    } else {
//      printf("fseek fail PFV");
//      size = 0;
//    }
//    answer = fclose(file_spot);
//    assert(answer == 0);
//  } else {
//    printf("file open fail PFV");
//    size = 0;
//  }
//  *paper_size = size;
//  // assert(*paper_size != 0);
//}

void text_file_addenda(const uint32_t text_long, const char *text,
                       const char *filename) {
  FILE *out = fopen(filename, "a");
  assert(out != NULL);
  uint32_t written_text_long = (uint32_t)fprintf(out, "%s", text);
  // printf("text_long %X \n", text_long);
  // printf("written_text_long %X \n", written_text_long);
  assert(written_text_long >= text_long);
  int result = fclose(out);
  assert(result == 0);
}

void brief_language_code_identity(const uint8_t language_code_long,
                                  const char *language_code,
                                  uint8_t *brief_code_long) {
  assert(language_code != NULL);
  assert(language_code_long > 0);
  *brief_code_long = 2;
}

void region_language_identity(uint8_t *produce_language_code_long,
                              char *produce_language_code) {
  assert(produce_language_code_long != NULL);
  assert(*produce_language_code_long >= 4);
  assert(produce_language_code != NULL);
  assert(produce_language_code[0] == (char)0);
  setlocale(LC_ALL, "");
  char language_code[16] = {0};
  strcpy(language_code, setlocale(LC_CTYPE, NULL));
  uint8_t language_code_long = (uint8_t)strlen(language_code);
  uint8_t brief_code_long = 2;
  brief_language_code_identity(language_code_long, language_code,
                               &brief_code_long);
  memcpy(produce_language_code, language_code, brief_code_long);
  *produce_language_code_long = brief_code_long;
}

void text_file_read(const char *filename, uint32_t *text_long, char *text) {
  uint32_t paper_indexFinger = 0;
  uint16_t paper_long = MAXIMUM_PAPER_MAGNITUDE;
  uint32_t max_text_long = *text_long;
  assert(*text_long > 0);
  char paper_text[MAXIMUM_PAPER_LONG] = {0};
  uint32_t inner_text_long = 0;
  for (paper_indexFinger = 0;
       paper_indexFinger < MAXIMUM_PAPER_MAGNITUDE && paper_long != 0;
       ++paper_indexFinger) {
    paper_long = MAXIMUM_PAPER_LONG;
    paper_read(filename, paper_indexFinger, &paper_long, paper_text);
  //printf("%s:%d paper_long 0x%X,\n", __FILE__, __LINE__,
  //       paper_long);
    assert(paper_long <= MAXIMUM_PAPER_LONG);
    assert(max_text_long >= inner_text_long + paper_long);
    if (paper_long > 0 && inner_text_long + paper_long <= max_text_long) {
      memcpy(text + inner_text_long, paper_text, paper_long);
    } else {
      break;
    }
    inner_text_long += paper_long;
    // clear paper and set paper long accordingly
    memset(paper_text, 0, MAXIMUM_PAPER_LONG);
  }
  *text_long = inner_text_long;
}
