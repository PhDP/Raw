#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../src/numbers.c"
#include "../src/compar.c"

int main() {
  assert(0 == rd_round(0));
  assert(-43 == rd_round(-42.7));
  assert(-8819 == rd_round(-8819.456));
  printf("%d\n", rd_round(2.5001));
  assert(1800 == rd_round(1799.6));
  assert(0 == rd_round(-0.5));
  assert(0 == rd_round(0.5));
  assert(-4 == rd_round(-3.5));
  assert(4 == rd_round(3.5));
  assert(-10 == rd_round(-10.5));
  assert(10 == rd_round(10.5));
  return EXIT_SUCCESS;
}
