#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "randamu/well1024.h"

int main() {
  rd_well1024 r;
  rd_well1024_init_time(&r);

  int i = 0;
  for (; i < 1024; ++i) {
    r.has_next = (i % 2 == 0);
    rd_well1024_normal(&r);
  }
  return EXIT_SUCCESS;
}

