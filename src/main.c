#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bogosort.h"
#include "well.h"
#include "compar.h"

int main(int argc, char **argv) {
  clock_t start = clock();
  const unsigned int seed = atoi(argv[1]);
  assert(seed <= 25);

  well rng;
  well_init(&rng, seed);

  /* Stuff to sort with the almighty Bogosort (it's so good it has to be capitalized). */
  int attempts[4]; /* Store the number of attempts for each sort. */
  double *x = (double*)malloc(sizeof(double) * seed);
  int *y = (int*)malloc(sizeof(int) * seed);
  for (int i = 0; i < seed; ++i) {
    x[i] = well_double(&rng);
    y[i] = well_int_max(&rng);
  }
  char *j_names[] = {"Midori", "Ryuu", "Itsuki", "Ryuuji", "Tomoto", "Mitsuki", "Chu", "Ichigo", "Ishiro", "Izuki", "Matsuri", "Yuu", "Hiraku", "Sora", "Hiro", "Hidenori", "Yusuke", "Sakura", "Midori", "Mizuki", "Kasumi", "Sora", "Tsukiko", "Sayuri", "Ao", "Aoki"};

  /* Sort 'x' in descending order: */
  attempts[0] = bogosort((void*)x, seed, sizeof(double), cmp_double_des, seed);

  /* Sort 'y' in ascending order: */
  attempts[1] = bogosort((void*)y, seed, sizeof(int), cmp_int_asc, seed);

  /* Sort the strings (as in a dictionnary): */
  attempts[2] = bogosort((void*)j_names, seed, sizeof(char*), cmp_string_asc, seed);

  printf("Seed: %u\n", seed);
  printf("Attempts: ");
  for (int i = 0; i < 3; ++i) {
    printf("%d ", attempts[i]);
  }
  printf("\n");
  printf("Time: %.8f", (double)(clock() - start) / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

