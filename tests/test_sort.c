#include <assert.h>
#include <string.h>
#include "../src/rng.c"
#include "../src/sort.c"
#include "../src/compar.c"

int main() {
  rd_rng r;
  rd_rng_init_time(&r);

  int x[] = {-308392, -20929, 4958933, -222234, 5020224, -1025, 1600390193, -1025};
  assert(rd_sorted(&x, 3, sizeof(int), cmp_int_asc));
  assert(!rd_sorted(&x, 8, sizeof(int), cmp_int_asc));
  assert(!rd_sorted(&x, 6, sizeof(int), cmp_int_des));

  //rd_bogosort(&x, 8, sizeof(int), cmp_int_asc, &r);
  rd_isort(&x, 8, sizeof(int), cmp_int_asc);
  assert(rd_sorted(&x, 8, sizeof(int), cmp_int_asc));

  rd_stdbogosort(&x, 8, sizeof(int), cmp_int_des);
  assert(rd_sorted(&x, 8, sizeof(int), cmp_int_des));

  for (int i = 0; i < 24; ++i) {
    const size_t size_y = rd_rng_intb(&r, 10) + 1;
    int *y = (int *)rd_randalloc(&r, size_y * sizeof(int));
    printf("Test %d (%d elements):\n", i, (int)size_y);
    printf("   unsorted(y): ");
    for (int j = 0; j < size_y; ++j) {
      printf("%d  ", y[j]);
    }
    printf("\n   sorted(y): ");
    rd_isort(y, size_y, sizeof(int), cmp_int_des);
    for (int j = 0; j < size_y; ++j) {
      printf("%d  ", y[j]);
    }
    printf("\n\n");
    assert(rd_sorted(y, size_y, sizeof(int), cmp_int_des));
    free(y);
  }

  for (int i = 0; i < 8; ++i) {
    const size_t size_y = rd_rng_intb(&r, 8) + 1;
    const size_t bytes = size_y * sizeof(int);
    int *yq = (int *)rd_randalloc(&r, bytes);
    int *yi = (int *)malloc(bytes);
    int *yb = (int *)malloc(bytes);

    memcpy(yi, yq, bytes);
    memcpy(yb, yq, bytes);

    qsort(yq, size_y, sizeof(int), cmp_int_asc);
    rd_isort(yi, size_y, sizeof(int), cmp_int_asc);
    rd_bogosort(yb, size_y, sizeof(int), cmp_int_asc, &r);

    assert(memcmp(yi, yq, bytes) == 0);
    assert(memcmp(yq, yb, bytes) == 0);

    free(yq);
    free(yb);
    free(yi);
  }
  
  return EXIT_SUCCESS;
}

