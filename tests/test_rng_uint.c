#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "randamu/well1024.h"

int main() {
  rd_well1024 r;
  rd_well1024_init_time(&r);
  const int max = 4096;
  double sum = 0;

  int i = 0;
  for (; i < max; ++i) {
    const unsigned int x = rd_well1024_uint(&r);
    sum += (double)x;
  }
  const double avr = sum / max;
  const double e = avr / UINT32_MAX; // ~0.5
  assert(e > 0.48 && e < 0.52); //
  return EXIT_SUCCESS;
}
