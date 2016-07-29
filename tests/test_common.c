#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "randamu/well1024.h"

int main() {
  rd_rng r;
  rd_rng_init_time(&r);

  int i = 0, j;
  for (; i < 32; ++i) {
    const size_t size = rd_rng_intb(&r, 32) + 2;
    int *x = (int *)rd_randalloc(&r, size * sizeof(int));
    for (j = 0; j < 4; ++j) {
      int a = rd_rng_intb(&r, size), b;
      do {
        b = rd_rng_intb(&r, size);
      } while (a == b);
      const int val_a = x[a], val_b = x[b];
      rd_swap(&x[a], &x[b], sizeof(int));
      assert(val_a == x[b]);
      assert(val_b == x[a]);
    }
    free(x);
  }
  return EXIT_SUCCESS;
}

