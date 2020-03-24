/**
 * @file grammatical_evolution.h
 * @brief Functions to use grammatical evolution to evolve programs, mathematical
 * functions, sentences, whatever you want, just use your imagination!
 */
#ifndef RAW_GRAMMATICAL_EVOLUTION_H_
#define RAW_GRAMMATICAL_EVOLUTION_H_

#include "raw/common.h"
#include "raw/grammar.h"
#include "raw/codons.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Stores all the information for grammatical evolution.
 */
typedef struct {
  size_t pop_size;     // Number of solutions considered.
  size_t codon_size;   // Number of integers in the codons (the solutions).
  size_t max_wrap;     // Do you allow wrapping? How many times? 0 is the correct answer.
  sfmt_t* rng;         // Random number generator.
  size_t elites;       // The top solutions to keep unchanged and use for the
  r_codons* codons;    // The population of solutions
  char** output;       // Output of the codons. NULL if the codon failed to generate a valid string.
  r_grammar* grammar;  // The grammar.
} r_ge;

/**
 * @brief Initializes an object for grammatical evolution and generate an
 * initial population of solutions.
 *
 * @param g           Uninitialized grammatical evolution object.
 * @param seed        Seed for the random number generator.
 * @param pop_size    Size of the population of solutions. Must be > 9.
 * @param elites      Number of solutions to keep unchanged and used to generate
 *                    the next batch of solutions. Must be at least 4 and
 *                    smaller or equal to pop_size.
 * @param codon_size  How many integers to generate strings. 100-1000 are good
 *                    numbers. Must be at least 10.
 * @param max_wrap    Whether you allow wrapping the integer sequence and if so,
 *                    how many times.
 * @param grammar     A string representing the grammar (see grammar folder for
 *                    examples).
 * @param err         Stores parsing errors. If NULL, errors will be ignored.
 */
void r_ge_init(r_ge* g, size_t seed, size_t pop_size, size_t elites,
               size_t codon_size, size_t max_wrap, const char* grammar,
               r_parsing_err* err);

/**
 * @brief Return an initialized object for grammatical evolution and generate an
 * initial population of solutions.
 *
 * @param seed        Seed for the random number generator.
 * @param pop_size    Size of the population of solutions. Must be > 9.
 * @param elites      Number of solutions to keep unchanged and used to generate
 *                    the next batch of solutions. Must be at least 4 and
 *                    smaller or equal to pop_size.
 * @param codon_size  How many integers to generate strings. 100-1000 are good
 *                    numbers. Must be at least 10.
 * @param max_wrap    Whether you allow wrapping the integer sequence and if so,
 *                    how many times.
 * @param grammar     A string representing the grammar (see grammar folder for
 *                    examples).
 * @param err         Stores parsing errors. If NULL, errors will be ignored.
 */
r_ge* r_ge_init_ptr(size_t seed, size_t pop_size, size_t elites,
                    size_t codon_size, size_t max_wrap, const char* grammar,
                    r_parsing_err* err);

/**
 * @brief Generates new solutions (g->codons) and new strings (g->output) given
 * an array of fitnesses (higher = better) for the previous generation's output.
 *
 * It's important to note that g->output may have NULL strings if the codon
 * fails to generate a string.
 *
 * @param g           Initialized grammatical evolution object.
 * @param fitnesses   Fitness for all outputs (must have the same number of
 *                    elements as g->pop_size).
 */
void r_ge_one_step(r_ge* g, double* fitnesses);

/**
 * @brief Frees memory.
 */
void r_ge_free(r_ge* g);

#ifdef __cplusplus
}
#endif

#endif
