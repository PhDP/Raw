#include "raw/grammatical_evolution.h"
#include <time.h>

// This is our fitness function, it compares two strings and measure how
// similar they are (1 = the same, 0 = completely different).
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
  // The grammar:
  const char* grammar = "<expr> ::= <letter> | <letter><expr>\n<letter> ::= a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z";

  // The word we're trying to evolve:
  const char* target = "symbolic";

  // Size of the string of integers used to evolve the strings:
  const size_t codon_size = 250;

  // Seed for the random number generator:
  const size_t seed = time(0);

  // Number of solutions being considered at a given moment:
  const size_t pop_size = 100;

  // Number of elites (those with the best fitness, left unchanged and used to
  // generate the next generation).
  const size_t elites = 10;

  // Number of time steps:
  const size_t max_steps = 10000;

  // Grammatical evolution object:
  r_ge ge;

  // Initializes a grammatical evolution object.
  // Important: this functions generates an initial set of solutions.
  r_ge_init(&ge, seed, pop_size, elites, codon_size, 0, grammar, NULL);

  size_t i;

  // Stores the fitness for each solution:
  double* fitnesses = (double*)malloc(pop_size * sizeof(double));

  // Computes the fitness for the initial solutions:
  for (i = 0; i < pop_size; ++i) {
    fitnesses[i] = fitness(ge.output[i], target);
  }

  size_t step = 0;
  for (; step < max_steps; ++step) {
    // Given the fitness for each solution, generates a new set of solutions:
    r_ge_one_step(&ge, fitnesses);

    // Print results and compute the fitness for the next step:
    printf("Step %lu:\n", step);
    for (i = 0; i < pop_size; ++i) {
      printf("  %s\n", ge.output[i]);
      fitnesses[i] = fitness(ge.output[i], target);
    }
    printf("\n\n");
  }

  // Free the memory of the grammatical evolution object:
  r_ge_free(&ge);
  free(fitnesses);

  return EXIT_SUCCESS;
}
