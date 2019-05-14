/**
 * @file codons.h
 * @brief Codons are used in grammatical evolution to generate strings from grammars.
 */
#ifndef RANDAMU_CODONS_H_
#define RANDAMU_CODONS_H_

#include "randamu/common.h"
#include "randamu/grammar.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A vector of codons used to generate strings from grammars.
 */
typedef struct {
  uint32_t* codons; // uint8_t is also commonly used.
  size_t nmemb;
} rd_codons;

/**
 * x@brief Initializes with a given number of members.
 * @param c     Struct to initialize.
 * @param nmemb Number of codons.
 */
void rd_codons_init(rd_codons* c, const size_t nmemb);

/**
 * @brief Initializes and fill with random numbers.
 * @param c
 * @param nmemb
 * @param rng     Random number generator
 */
void rd_codons_random_init(rd_codons* c, const size_t nmemb, sfmt_t* rng);

/**
 * @brief Fills an initialized rd_codons with random numbers.
 */
void rd_codons_random_fill(rd_codons* c, sfmt_t* rng);

void rd_codons_cpy(rd_codons* dest, const rd_codons* src);

/**
 * @brief Generate a string from a given codon and grammar.
 *
 * @param c         The codons used to generate the string.
 * @param g         The grammar.
 * @param max_wrap  Maximum number of times the algorithms is allowed to wrap around the codons (set to 0 for no wrapping).
 * @return          The generated string or null in case of error or if and all codons were used.
 */
char* rd_codons_generate(const rd_codons* c, const rd_grammar* g, const size_t max_wrap);

void rd_codons_show(const rd_codons* c, FILE* out);

void rd_codons_free(rd_codons* c);

#ifdef __cplusplus
}
#endif

#endif
