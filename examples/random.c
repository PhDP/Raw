// Compile with:
//   $ gcc -O3 random.c -o random -lrandamu -lm

#include <stdlib.h>
#include <stdio.h>
#include <randamu/xorshift1024.h>

int main() {
  rd_xs1024 r; // A random number generator.
  rd_xs1024_init_time(&r); // Initialize with the current time.
  printf("Yeee, random numbers!\n");
  for (int i = 0; i < 42; ++i) {
    // Generates double-precision numbers in the [0, 1) range.
    printf("%f\n", rd_xs1024_double(&r));
  }
  return EXIT_SUCCESS;
}

