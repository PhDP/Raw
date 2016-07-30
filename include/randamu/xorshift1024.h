/*! \file
 *
 * \brief Sebastiano Vigna's xorshift1014* algorithm for random numbers.
 */
#ifndef RANDAMU_XS1024_RNG_H_
#define RANDAMU_XS1024_RNG_H_

#include <stdint.h>
#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint64_t state[16];
  int p; // size_t p???
} rd_xs1024;

/**
 * \brief Initializes a xoroshiro128+ generator with a seed and the splitmix64
 *        generator.
 */
void rd_xs1024_init(rd_xs1024 *r, uint64_t seed);

/**
 * \brief Initializes a xoroshiro128+ generator with a time and the splitmix64
 *        generator.
 */
void rd_xs1024_init_time(rd_xs1024 *r);

/**
 * \brief Returns the next 64-bit integer.
 */
uint64_t rd_xs1024_next(rd_xs1024 *r);

/**
 * \brief Returns the next number in the [0, 1) range.
 */
double rd_xs1024_double(rd_xs1024 *r);

/**
 * \brief Return a double from the normal distribution.
 *
 * \param rng       The generator.
 * \return          An exponential random variable.
 */
double rd_xs1024_normal(rd_xs1024 *r);

/**
 * \brief Returns a double from the exponential distribution (between 0 and 1).
 *
 * \param rng       The generator.
 * \return          An exponential random variable.
 */
double rd_xs1024_exp(rd_xs1024 *r);

/**
 * \brief Returns an integer from a poisson distribution given lambda.
 *
 * \param rng       The generator.
 * \param lambda    The lambda parameter of the poisson distribution.
 * \return          A number in the poisson distribution.
 */
int rd_xs1024_poisson(rd_xs1024 *r, double lambda);

/**
  \brief This is the jump function for the generator. It is equivalent
         to 2^512 calls to next(); it can be used to generate 2^512
         non-overlapping subsequences for parallel computations.
 */
void rd_xs1024_jump(rd_xs1024 *r);

#ifdef __cplusplus
}
#endif

#endif
