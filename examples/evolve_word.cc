#include "raw/codons.h"
#include "raw/grammatical_evolution.h"
#include <time.h>

double fitness(const char* x, const char* y) {
  const size_t x_len = strlen(x);
  const size_t y_len = strlen(y);
  const size_t min_len = x_len < y_len? x_len : y_len;
  const size_t max_len = x_len > y_len? x_len : y_len;

  size_t same = 0, i = 0;
  for (; i < min_len; ++i) {
    same += x[i] == y[i];
  }
  return ((double)same) / max_len;
}

int main(int argc, char** argv) {
  const char* str = "<expr> ::= <letter> | <letter><expr>\n<letter> ::= a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z";
  const char* target = "symbolic";
  const size_t codon_size = 250;
  const size_t seed = time(0);
  const size_t pop_size = 100;

  printf("Codon size: %lu\n", codon_size);
  printf("Seed: %lu\n", seed);

  // Grammatical evolution object:
  r_ge ge;

  // Initializes with a population size of 1000 (50 elites):
  r_ge_init(&ge, seed, pop_size, 10, codon_size, 0, str, NULL);

  size_t i;

  double* fitnesses = (double*)malloc(pop_size * sizeof(double));
  for (i = 0; i < pop_size; ++i) {
    fitnesses[i] = fitness(ge.output[i], target);
  }

  size_t step = 0;
  for (; step < 10000; ++step) {
    r_ge_one_step(&ge, fitnesses);
    printf("Step %lu:\n", step);
    for (i = 0; i < pop_size; ++i) {
      printf("  %s\n", ge.output[i]);
      fitnesses[i] = fitness(ge.output[i], target);
    }
    printf("\n\n");
  }

  r_ge_free(&ge);

  return EXIT_SUCCESS;
}
