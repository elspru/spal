#include "dialogue.h"
#include <assert.h>
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
