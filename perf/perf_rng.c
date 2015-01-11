#include <stdlib.h>
#include <stdio.h>
#include <randamu/rng.h>
#include "stopwatch.c"

int main() {
  rd_stopwatch sw;
  rd_sw_init(&sw);
  rd_rng r;
  rd_rng_init_time(&r);
  const uint64_t max = (1 << 30);
  double sum = 0.0;

  uint64_t i = 0;
  for (; i < max; ++i) {
    sum += rd_rng_double(&r);
  }

  assert(sum > 0.0);
  printf("Time: %lu\n", rd_sw_term(&sw));
  return EXIT_SUCCESS;
}
