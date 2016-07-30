#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "randamu/stats.h"

double rd_sort_stat(const double* base, size_t nmemb,
                    double (*st)(const double*, size_t)) {
  double *sorted = (double*)malloc(nmemb * sizeof(double));
  memcpy((void *)sorted, (void *)base, nmemb * sizeof(double));
  qsort((void *)sorted, nmemb, sizeof(double), cmp_double_asc);
  const double res = st(sorted, nmemb);
  free(sorted);
  return res;
}

void rd_mean_var(const double *x, size_t nmemb, double *mean, double *var) {
  double m = 0.0;
  double m2 = 0.0;
  double delta;

  int i = 0;
  for (; i < nmemb; ++i) {
    delta = x[i] - m;
    m += delta / (i + 1);
    m2 += delta * (x[i] - m);
  }

  if (mean != NULL)
    *mean = m;
  if (var != NULL)
    *var = m2 / (nmemb - 1);
}

double rd_mean(const double *x, size_t nmemb) {
  double mean = 0.0;
  double delta;

  int i = 0;
  for (; i < nmemb; ++i) {
    delta = x[i] - m;
    mean += delta / (i + 1);
  }

  return mean;
};

double rd_var(const double *x, size_t nmemb) {
  double var;
  rd_mean_var(x, nmemb, NULL, &var);
  return var;
}

double rd_std(const double *x, size_t nmemb) {
  return sqrt(rd_var(x, nmemb));
}

double rd_kutorsis(const double *x, size_t nmemb) {
  double m1 = 0.0, m2 = 0.0, m3 = 0.0, m4 = 0.0;
  double i1, term1, delta, delta_n, delta_n2;

  int i = 0;
  for (; i < nmemb; ++i) {
    i1 = (double)(i + 1);
    delta = x[i] - m1;
    delta_n = delta / i1;
    delta_n2 = delta_n * delta_n;
    term1 = delta * delta_n * i;
    m1 += delta_n;
    m4 += term1 * delta_n2 * (i1 * i1 - 3 * i1 + 3) + 6 * delta_n2 * m2 - 4 * delta_n * m3;
    m3 += term1 * delta_n * (i1 - 2) - 3 * delta_n * m2;
    m2 += term1;
  }
  return (nmemb * m4) / (m2 * m2) - 3;
}

