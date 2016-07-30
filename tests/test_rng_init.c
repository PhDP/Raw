#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "randamu/well1024.h"

int main() {
  rd_well1024 r;
  assert(6 == rd_well1024_init(&r, 6));
  assert(42 == rd_well1024_init(&r, 0));
  assert(rd_well1024_init_time(&r) > 0);
  assert(r.seed != 0);
  return EXIT_SUCCESS;
}

