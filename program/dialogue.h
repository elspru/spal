#ifndef DIALOGUE_H
#define DIALOGUE_H
#define MAXIMUM_PAPER_LONG 4096
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#define MAXIMUM_PAPER_LONG 4096
#define MAXIMUM_PAPER_MAGNITUDE 4096

void paper_read(const char *file_name, const size_t paper_number,
                       uint16_t *paper_size, char *paper_storage) ;

void paper_write(const char *file_name, const size_t paper_number,
                        uint16_t paper_size, char *paper_storage);
void text_file_addenda(const uint32_t text_long, const char *text,
                       const char *filename);
void text_file_read(const char *filename, uint32_t * text_long, char *text);

void region_language_identity();
#endif
