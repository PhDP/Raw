#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bogosort.h"
#include "rng.h"

void knuth_shuffle(void *base, size_t nmemb, size_t size, rd_rng *r) {
  unsigned char swap[size];
  int x;
  for (size_t i = nmemb - 1; i > 0; --i) {
    x = rd_int(r, i + 1);
    memcpy(&swap[0], (void*)((unsigned char*)base + x * size), size);
    memcpy((void*)((unsigned char*)base + (x * size)), (void*)((unsigned char*)base + (i * size)), size);
    memcpy((void*)((unsigned char*)base + (i * size)), &swap[0], size);
  }
}

