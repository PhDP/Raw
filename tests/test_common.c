#include <assert.h>
#include <string.h>
#include "common.h"
#include "../src/rng.c"

int main() {
  rd_rng r;
  rd_rng_init_time(&r);

  for (int i = 0; i < 32; ++i) {
    const size_t size = rd_rng_intb(&r, 32) + 2;
    int *x = (int *)rd_randalloc(&r, size * sizeof(int));
    printf("Swapping test #%d (%d elements):\n", i, (int)size);
    printf("   before swapping: ");
    for (int j = 0; j < size; ++j) {
      printf("%d  ", x[j]);
    }
    printf("\n   swaps: ");
    for (int j = 0; j < 4; ++j) {
      int a = rd_rng_intb(&r, size), b;
      do {
        b = rd_rng_intb(&r, size);
      } while (a == b);
      const int val_a = x[a], val_b = x[b];
      printf("(%d, %d) ", a, b);
      rd_swap(&x[a], &x[b], sizeof(int));
      assert(val_a == x[b]);
      assert(val_b == x[a]);
    }
    printf("\n   after swapping: ");
    for (int j = 0; j < size; ++j) {
      printf("%d  ", x[j]);
    }
    printf("\n\n");
    free(x);
  }
  return EXIT_SUCCESS;
}

