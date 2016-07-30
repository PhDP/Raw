#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "randamu/well1024.h"

int main() {
  rd_well1024 r;
  rd_well1024_init_time(&r);
  printf("Seed: %u\n", r.seed);

  assert(sizeof(uint8_t) == 1);
  assert(sizeof(uint16_t) == 2);
  assert(sizeof(uint32_t) == 4);
  assert(sizeof(uint64_t) == 8);

  const size_t max = 2048 + rd_well1024_uintb(&r, 500);
  printf("Max: %u\n", (uint32_t)max);

  double sum8 = 0.0, sum16 = 0.0, sum32 = 0.0, sum64 = 0.0;

  uint8_t * arr8 = (uint8_t *)calloc(max, sizeof(uint8_t));
  uint16_t * arr16 = (uint16_t *)calloc(max, sizeof(uint16_t));
  uint32_t * arr32 = (uint32_t *)calloc(max, sizeof(uint32_t));
  uint64_t * arr64 = (uint64_t *)calloc(max, sizeof(uint64_t));

  size_t i = 0;
  for (; i < max; ++i) {
    sum8 += (double)arr8[i];
    sum16 += (double)arr16[i];
    sum32 += (double)arr32[i];
    sum64 += (double)arr64[i];
  }

  assert(sum8 == 0.0);
  assert(sum16 == 0.0);
  assert(sum32 == 0.0);
  assert(sum64 == 0.0);

  free(arr8);
  free(arr16);
  free(arr32);
  free(arr64);

  arr8 = (uint8_t *)rd_randalloc(&r, max * sizeof(uint8_t));
  arr16 = (uint16_t *)rd_randalloc(&r, max * sizeof(uint16_t));
  arr32 = (uint32_t *)rd_randalloc(&r, max * sizeof(uint32_t));
  arr64 = (uint64_t *)rd_randalloc(&r, max * sizeof(uint64_t));

  for (i = 0; i < max; ++i) {
    sum8 += (double)arr8[i];
    sum16 += (double)arr16[i];
    sum32 += (double)arr32[i];
    sum64 += (double)arr64[i];
  }

  const double e8 = (sum8 / max) / UINT8_MAX;
  assert(e8 > 0.48 && e8 < 0.52);

  const double e16 = (sum16 / max) / UINT16_MAX;
  assert(e16 > 0.48 && e16 < 0.52);

  const double e32 = (sum32 / max) / UINT32_MAX;
  assert(e32 > 0.48 && e32 < 0.52);

  const double e64 = (sum64 / max) / UINT64_MAX;
  assert(e64 > 0.48 && e64 < 0.52);

  // Make sure that arbitrarily small rd_randalloc works fine too.
  uint32_t allsamples = 0;
  double sumS = 0.0;
  for (i = 0; i < 100; ++i) {
    const uint32_t sample = rd_well1024_uintb(&r, 100) + 1;
    arr8 = (uint8_t *)rd_randalloc(&r, max * sizeof(uint8_t));
    size_t j = 0;
    for (; j < sample; ++j) {
      sumS += (double)arr8[j];
    }
    free(arr8);
    allsamples += sample;
  }
  const double es = (sumS / allsamples) / UINT8_MAX;
  assert(es > 0.45 && es < 0.55);

  assert(rd_randalloc(&r, 0) == NULL);

  printf("%f\n", e8);
  printf("%f\n", e16);
  printf("%f\n", e32);
  printf("%f\n", e64);
  printf("%f\n", es);

  free(arr16);
  free(arr32);
  free(arr64);

  return EXIT_SUCCESS;
}

