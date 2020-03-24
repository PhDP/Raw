#include "raw/grammatical_evolution.h"
#include "raw/cmp.h"

void r_ge_init(r_ge* g, size_t seed, size_t pop_size, size_t elites,
               size_t codon_size, size_t max_wrap, const char* grammar,
               r_parsing_err* err) {
  g->pop_size = pop_size;
  if (g->pop_size < 10) {
    g->pop_size = 10;
  }

  g->elites = elites;
  if (g->elites > g->pop_size) {
    g->elites = g->pop_size;
  }
  if (g->elites < 4) {
    g->elites = 4;
  }

  g->codon_size = codon_size;
  if (g->codon_size < 10) {
    g->codon_size = 10;
  }

  g->max_wrap = max_wrap;
  g->codons = NULL;
  g->output = NULL;

  g->rng = (sfmt_t*)malloc(sizeof(sfmt_t));
  sfmt_init_gen_rand(g->rng, seed);

  g->grammar = (r_grammar*)malloc(sizeof(r_grammar));
  r_grammar_init_from_str(g->grammar, grammar, err);

  g->codons = (r_codons*)malloc(g->pop_size * sizeof(r_codons));
  g->output = (char**)malloc(g->pop_size * sizeof(char*));
  size_t i = 0;
  while (i < g->pop_size) {
    r_codons_random_init(&g->codons[i], g->codon_size, g->rng);
    g->output[i] = r_codons_generate(&g->codons[i], g->grammar, g->max_wrap);
    if (g->output[i]) {
      ++i;
    } else {
      r_codons_free(&g->codons[i]);
    }
  }
}

static size_t find_min(double* xs, size_t nmemb) {
  size_t min = 0;
  size_t i = 1;
  for (; i < nmemb; ++i) {
    if (xs[i] < xs[min]) {
      min = i;
    }
  }
  return min;
}

void r_ge_one_step(r_ge* g, double* fitnesses) {
  // Yes, this would be a lot simpler with a good multi{set, map}:
  const size_t codon_size = g->codon_size;
  const size_t elites = g->elites;
  size_t* elites_id = (size_t*)malloc(elites * sizeof(size_t));
  double* elites_fit = (double*)malloc(elites * sizeof(double));
  size_t worst_elite_id = 0; // Refers to the ID in elites_id, it's an ID of IDs.

  // Find the elites:
  size_t i = 0;
  for (; i < elites; ++i) {
    elites_id[i] = i;
    elites_fit[i] = fitnesses[i];
    if (fitnesses[elites_id[worst_elite_id]] > fitnesses[i]) {
      worst_elite_id = i;
    }
  }

  for (; i < g->pop_size; ++i) {
    if (fitnesses[i] > fitnesses[elites_id[worst_elite_id]]) {
      elites_id[worst_elite_id] = i;
      elites_fit[worst_elite_id] = fitnesses[i];
      worst_elite_id = find_min(elites_fit, elites);
    }
  }

  qsort((void*)elites_id, elites, sizeof(size_t), r_cmp_sz_asc);
  free(elites_fit); // Meaningless after the sort.

  for (i = 0; i < g->pop_size; ++i) {
    // Only do something if it's not found in the set of elites:
    if (bsearch((const void*)(&i), (const void*)elites_id, elites,
                sizeof(size_t), r_cmp_sz_asc) == NULL) {

      // Select two parents:
      const size_t parent0 = elites_id[(size_t)(sfmt_genrand_real2(g->rng)
                                       * elites)];
      const size_t parent1 = elites_id[(size_t)(sfmt_genrand_real2(g->rng)
                                       * elites)];

      // Crossover point
      // Only perform crossover if the parents are different (dah!):
      if (parent0 != parent1) {
        const size_t crossover = (size_t)(sfmt_genrand_real2(g->rng)
                                          * codon_size);
        size_t c = 0;
        for (; c < crossover; ++c) {
          g->codons[i].codons[c] = g->codons[parent0].codons[c];
        }
        for (; c < g->codon_size; ++c) {
          g->codons[i].codons[c] = g->codons[parent1].codons[c];
        }
      }

      // Mutations:

      size_t mutations = 1;
      size_t k = 0;
      for (; k < 20; ++k) {
        if (sfmt_genrand_real2(g->rng) < 0.1) {
          ++mutations;
        }
      }

      for (k = 0; k < mutations; ++k) {
        g->codons[i].codons[((size_t)(sfmt_genrand_real2(g->rng)
                            * codon_size))] = sfmt_genrand_uint32(g->rng);
      }

      if (g->output[i]) {
        free((void*)g->output[i]);
      }
      g->output[i] = r_codons_generate(&g->codons[i], g->grammar, g->max_wrap);

    }
  }

  free(elites_id);
}

void r_ge_free(r_ge* g) {
  if (g) {
    if (g->rng) {
      free(g->rng); // Leaking memory? No free function from SFMT.
    }
    if (g->codons) {
      size_t i = 0;
      for (; i < g->pop_size; ++i) {
        r_codons_free(&g->codons[i]);
      }
      free(g->codons);
    }
    if (g->output) {
      size_t i = 0;
      for (; i < g->pop_size; ++i) {
        if (g->output[i]) {
          free(g->output[i]);
        };
      }
      free(g->output);
    }
    r_grammar_free(g->grammar);
  }
}
