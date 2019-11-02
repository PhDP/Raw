/**
 * @file codons.h
 * @brief Codons are used in grammatical evolution to generate strings from grammars.
 */
#ifndef RAW_CODONS_H_
#define RAW_CODONS_H_

#include "raw/common.h"
#include "raw/grammar.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A vector of codons used to generate strings from grammars.
 */
typedef struct {
  uint32_t* codons; // uint8_t is also commonly used.
  size_t nmemb;
} r_codons;

/**
 * x@brief Initializes with a given number of members.
 * @param c     Struct to initialize.
 * @param nmemb Number of codons.
 */
void r_codons_init(r_codons* c, const size_t nmemb);

/**
 * @brief Initializes and fill with random numbers.
 * @param c
 * @param nmemb
 * @param rng     Random number generator
 */
void r_codons_random_init(r_codons* c, const size_t nmemb, sfmt_t* rng);

/**
 * @brief Fills an initialized r_codons with random numbers.
 */
void r_codons_random_fill(r_codons* c, sfmt_t* rng);

void r_codons_cpy(r_codons* dest, const r_codons* src);

/**
 * @brief Generate a string from a given codon and grammar.
 *
 * @param c         The codons used to generate the string.
 * @param g         The grammar.
 * @param max_wrap  Maximum number of times the algorithms is allowed to wrap around the codons (set to 0 for no wrapping).
 * @return          The generated string or null in case of error or if and all codons were used.
 */
char* r_codons_generate(const r_codons* c, const r_grammar* g, const size_t max_wrap);

void r_codons_show(const r_codons* c, FILE* out);

void r_codons_free(r_codons* c);

#ifdef __cplusplus
}
#endif

#endif
