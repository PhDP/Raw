#include "raw/codons.h"
#include "raw/grammatical_evolution.h"
#include <time.h>

int main(int argc, char** argv) {
  const char* str = "<expr>      ::= dS/dt = <formula>\\ndI/dt = <formula>\\ndR/dt = <formula>\n<formula>   ::= <formula> <operator> <formula> | <formula> <operator> <variable> | <variable> <operator> <formula> | <unary><variable> | <variable>\n<unary>     ::= -\n<operator>  ::= - | *\n<variable>  ::= a | b | I | S\n";
  const size_t codon_size = argc > 1? atoi(argv[1]) : 100;
  const size_t seed = argc > 2? atoi(argv[2]) : time(0);
  const size_t pop_size = 1000;

  printf("Codon size: %lu\n", codon_size);
  printf("Seed: %lu\n", seed);

  // Grammatical evolution object:
  r_ge ge;

  // Initializes with a population size of 1000 (50 elites):
  r_ge_init(&ge, seed, pop_size, 50, codon_size, 0, str, NULL);

  size_t i = 0;
  for (; i < pop_size; ++i) {
    printf("%s\n", ge.output[i]);
  }

  r_ge_free(&ge);

  return EXIT_SUCCESS;
}
