#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "randamu/numbers.h"
#include "randamu/compar.h"

int rd_round(double n) {
  const int floor = (int)n;
  const double rem = n >= 0 ? n - floor : floor - n;
  if (rem < 0.5) {
    return floor;
  } else if (rem > 0.5) {
    return n > 0 ? floor + 1 : floor - 1;
  } else if (floor % 2 == 0) {
    return floor;
  }
  return n > 0 ? floor + 1 : floor - 1;
}

int rd_round_odd(double n) {
  const int floor = (int)n;
  const double rem = n >= 0 ? n - floor : floor - n;
  if (rem < 0.5) {
    return floor;
  } else if (rem > 0.5) {
    return n > 0 ? floor + 1 : floor - 1;
  } else if (floor % 2 != 0) {
    return floor;
  }
  return n > 0 ? floor + 1 : floor - 1;
}

double rd_sortsum(const double *base, int nmemb) {
  double *sorted = (double *)malloc(nmemb * sizeof(double));
  memcpy((void *)sorted, (void *)base, nmemb * sizeof(double));
  qsort((void *)sorted, nmemb, sizeof(double), cmp_double_asc);
  double sum = 0.0;

  int i = 0;
  for (; i < nmemb; ++i) {
    sum += sorted[i];
  }
  free(sorted);
  return sum;
}
