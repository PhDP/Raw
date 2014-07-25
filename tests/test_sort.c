#include <assert.h>
#include "../src/rng.c"
#include "../src/sort.c"
#include "../src/compar.c"

int main() {
  rd_rng r;
  rd_rng_init_time(&r);

  int x[] = {-3, -2, -1, 0, 5, 10, 16, 10};
  assert(rd_sorted(&x, 7, sizeof(int), cmp_int_asc));
  assert(!rd_sorted(&x, 8, sizeof(int), cmp_int_asc));
  assert(!rd_sorted(&x, 7, sizeof(int), cmp_int_des));

  rd_bogosort(&x, 8, sizeof(int), cmp_int_asc, &r);
  assert(rd_sorted(&x, 8, sizeof(int), cmp_int_asc));

  rd_stdbogosort(&x, 8, sizeof(int), cmp_int_des);
  assert(rd_sorted(&x, 8, sizeof(int), cmp_int_des));
  return EXIT_SUCCESS;
}
