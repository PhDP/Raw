#include <assert.h>
#include "../src/rng.c"

int main() {
  rd_rng r;
  assert(6 == rd_rng_init(&r, 6));
  assert(42 == rd_rng_init(&r, 0));
  assert(rd_rng_init_time(&r) > 0);
  return EXIT_SUCCESS;
}

