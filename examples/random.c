#include <stdlib.h>
#include <stdio.h>
#include <randamu/well1024.h>

int main() {
  rd_well1024 r; // A random number generator.
  rd_well1024_init_time(&r); // Initialize with the current time.
  printf("Yeee, random numbers!\n");
  for (int i = 0; i < 42; ++i) {
    // Generates double-precision numbers in the [0, 1) range.
    printf("%f\n", rd_well1024_double(&r));
  }
  printf("\nRandom 32-bit unsigned integers:\n");
  for (int i = 0; i < 28; ++i)
    printf("%lu\n", rd_well1024_uint(&r));
  return EXIT_SUCCESS;
}

