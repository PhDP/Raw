#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "numbers.h"
#include "compar.h"

int rd_round(double n) {
  const int floor = (int)n;
  const double rem = n - floor;
  if (rem < 0.5) {
    return floor;
  } else if (rem > 0.5) {
    return floor > 0? floor + 1 : floor - 1;
  } else if (floor % 2 == 0) {
    return floor;
  }
  return floor > 0? floor + 1 : floor - 1;
}

double rd_sortsum(const double *base, int nmemb) {
  double *sorted = (double*)malloc(nmemb * sizeof(double));
  memcpy((void*)sorted, (void*)base, nmemb * sizeof(double));
  qsort((void*)sorted, nmemb, sizeof(double), cmp_double_asc);
  double sum = 0.0;
  for (int i = 0; i < nmemb; ++i) {
    sum += sorted[i];
  }
  free(sorted);
  return sum;
}

