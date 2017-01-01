#ifndef AGREE_H
#define AGREE_H

#ifndef HOLY
#define local 
#define global
#endif
#define NEWSPAPER_LONG 0x10


#ifndef NDEBUG
void v16us_agree(const int circumstance, const v16us error_news,
           local uint16_t *newspaper_indexFinger, global v16us *newspaper) {
  uint16_t program_indexFinger = *newspaper_indexFinger;
  if (*newspaper_indexFinger < NEWSPAPER_LONG) {
    if (!circumstance) {
      if (program_indexFinger < NEWSPAPER_LONG) {
        newspaper[program_indexFinger] = error_news;
      } else {
        newspaper[*newspaper_indexFinger] = error_news;
      }
      *newspaper_indexFinger += 1;
    }
  }
}
void agree(const int circumstance, const char * pyash_text,
           local uint16_t *newspaper_indexFinger, global v16us *newspaper) {
  if (!circumstance) {
    uint16_t text_long = (uint16_t) strlen(pyash_text);
    uint16_t text_remainder = 0;
    uint16_t tablet_long = 1;
    v16us tablet = {0};
    text_encoding(text_long, pyash_text, &tablet_long, &tablet, &text_remainder);
    v16us_agree(circumstance, tablet, newspaper_indexFinger, newspaper);
  }
  return;
}
#else
void agree(const int circumstance, const v16us error_news,
           local uint8_t *newspaper_indexFinger, global v16us *newspaper) {
  return;
}
#endif
#endif
