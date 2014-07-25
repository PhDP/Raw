#include <assert.h>
#include "../src/sorted.c"
#include "../src/compar.c"

int main() {
  int x[] = {-3, -2, -1, 0, 5, 10, 16, 10};
  assert(sorted(&x, 7, sizeof(int), cmp_int_asc));
  assert(!sorted(&x, 8, sizeof(int), cmp_int_asc));
  assert(!sorted(&x, 7, sizeof(int), cmp_int_des));
  return EXIT_SUCCESS;
}
