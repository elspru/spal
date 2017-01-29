#ifndef DIALOGUE_H
#define DIALOGUE_H
#define MAXIMUM_PAPER_LONG 4096
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void paper_read(const char *file_name, const size_t paper_number,
                       uint16_t *paper_size, char *paper_storage) ;

void text_file_addenda(const int text_long, const char *text,
                       const char *filename);

void region_language_identity();
#endif
