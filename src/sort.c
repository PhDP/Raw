#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "rng.h"
#include "sort.h"

bool rd_sorted(const void *base, size_t nmemb, size_t size,
               int (*cmp)(const void *, const void *)) {
  if (nmemb < 2) {
    return true;
  }
  register uint8_t *a = (uint8_t *)base, *b = (uint8_t *)base + size,
                   *end = (uint8_t *)base + (size * nmemb);
  while (b != end) {
    if (cmp((void *)a, (void *)b) > 0) {
      return false;
    }
    a = b, b += size;
  }
  return true;
}

void rd_knuth_shuffle(void *base, size_t nmemb, size_t size, rd_rng *r) {
  uint8_t *swap = (uint8_t *)malloc(size);
  int x;
  size_t i = nmemb - 1;
  for (; i > 0; --i) {
    x = rd_rng_intb(r, i + 1);
    memcpy((void *)swap, (void *)((uint8_t *)base + x * size), size);
    memcpy((void *)((uint8_t *)base + (x * size)),
           (void *)((uint8_t *)base + (i * size)), size);
    memcpy((void *)((uint8_t *)base + (i * size)), swap, size);
  }
  free(swap);
}

size_t rd_bogosort(void *base, size_t nmemb, size_t size,
                   int (*cmp)(const void *, const void *), rd_rng *r) {
  size_t attempts = 0;
  while (!rd_sorted(base, nmemb, size, cmp)) {
    ++attempts;
    rd_knuth_shuffle(base, nmemb, size, r);
  }
  return attempts;
}

void rd_stdbogosort(void *base, size_t nmemb, size_t size,
                    int (*cmp)(const void *, const void *)) {
  rd_rng r;
  rd_rng_init_time(&r);
  rd_bogosort(base, nmemb, size, cmp, &r);
}

void rd_isort(void *base, size_t nmemb, size_t size,
              int (*cmp)(const void *, const void *)) {
  uint8_t *swap = (uint8_t *)malloc(size);
  const uint8_t *end = (uint8_t *)base + nmemb * size;
  uint8_t *i = (uint8_t *)base + size;
  while (i != end) {
    memcpy(swap, (void *)i, size);
    uint8_t *j = i;
    while ((void *)j > base && cmp(swap, j - size) < 0) {
      memcpy((void *)j, (void *)(j - size), size);
      j -= size;
    }
    memcpy((void *)j, swap, size);
    i += size;
  }
  free(swap);
}

void * rd_median_of_three(void *base, size_t nmemb, size_t size,
                          int (*cmp)(const void *, const void *)) {
  void * med = (void*)((uint8_t *)base + (nmemb / 2) * size);
  const void * last = (void*)((uint8_t *)base + (nmemb - 1) * size);
  if (cmp(last, base) < 0) {
    rd_swap(last, base, size);
  }
  if (cmp(med, base) < 0) {
    rd_swap(med, base, size);
  }
  if (cmp(last, med) < 0) {
    rd_swap(last, med, size);
  }
  return med;
}

