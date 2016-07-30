#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <randamu/xorshift1024.h>

int main(int argc, char **argv) {
  const clock_t start = clock();
  rd_xs1024 r; // A random number generator.
  rd_xs1024_init(&r, time(NULL)); // Initialize with the current time.
  const uint64_t n = argc > 1? atoi(argv[1]) : 100000000;
  printf("Estimating pi with %lu random points.\n", n);
  uint64_t success = 0, i = 0;
  for (; i < n; ++i) {
    // Creates points in the unit square:
    const double x = rd_xs1024_double(&r);
    const double y = rd_xs1024_double(&r);
    // Tests if they are within the unit circle:
    success += (x * x + y * y) < 1.0;
  }
  // Print estimate of pi:
  printf("Pi ~= %f!\n", 4.0 * success / n);
  printf("Time: %.4f seconds.\n", ((double)(clock() - start) / CLOCKS_PER_SEC));
  return EXIT_SUCCESS;
}
