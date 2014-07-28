#include <stdlib.h>
#include <stdio.h>
#include <randamu/rng.h>

int main() {
  rd_rng r; // A random number generator.
  rd_rng_init_time(&r); // Initialize with the current time.
  printf("Yeee, random numbers!\n");
  for (int i = 0; i < 42; ++i) {
    // Generates double-precision numbers in the [0, 1) range.
    printf("%f\n", rd_rng_double(&r));
  }
  return EXIT_SUCCESS;
}

