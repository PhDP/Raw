#include "randamu/codons.h"
#include <time.h>

int main(int argc, char** argv) {
  const char* str = "<expr>    ::= <expr> <op> <expr> | <fun1>(<expr>) | <fun2>(<expr>, <expr>) | x[<idx>] | <real>\n<op>      ::= * | + | - | /\n<fun1>    ::= sin | cos | exp\n<fun2>    ::= pow\n<idx>     ::= 0 | 1 | 2\n<real>    ::= <integer>.<integer>\n<integer> ::= <integer><integer> | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9";
  const size_t codon_size = argc > 1? atoi(argv[1]) : 100;

  printf("Codon size: %lu\n", codon_size);

  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);

  sfmt_t rng;
  sfmt_init_gen_rand(&rng, time(0));

  rd_codons c;
  rd_codons_init(&c, codon_size);

  size_t i = 0;
  for (; i < 10000; ++i) {
    rd_codons_random_fill(&c, &rng);
    char* s = rd_codons_generate(&c, &g, 1);
    if (s) {
      printf("%lu: %s\n", i, s);
      free(s);
    } else {
      printf("%lu: Failed!\n", i);
    }
  }

  rd_grammar_free(&g);
  rd_codons_free(&c);

  return EXIT_SUCCESS;
}
