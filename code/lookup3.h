#ifndef LOOKUP3_H
#define LOOKUP3_H

void hashlittle2(const void *key, /* the key to hash */
                 size_t length,   /* length of the key */
                 uint32_t *pc,    /* IN: primary initval, OUT: primary hash */
                 uint32_t *pb); /* IN: secondary initval, OUT: secondary hash */
void hashlittle64(const size_t length, /* length of the key */
                  const void *key,     /* the key to hash */
                  uint64_t *hash); /* IN: primary initval, OUT: primary hash */
#endif
