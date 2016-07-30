#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(int argc, char **argv) {
  const clock_t start = clock();
  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, time(NULL)); // Seed with time
  const uint64_t n = argc > 1? atoi(argv[1]) : 100000000;
  printf("Estimating pi with %lu random points.\n", n);
  uint64_t success = 0, i = 0;
  for (; i < n; ++i) {
    // Creates points in the unit square:
    const double x = gsl_rng_uniform(r);
    const double y = gsl_rng_uniform(r);
    // Tests if they are within the unit circle:
    success += (x * x + y * y) < 1.0;
  }
  // Print estimate of pi:
  printf("Pi ~= %f!\n", 4.0 * success / n);
  printf("Time: %.4f seconds.\n", ((double)(clock() - start) / CLOCKS_PER_SEC));
  return EXIT_SUCCESS;
}
