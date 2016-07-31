/*! \file
 *
 * \brief Sebastiano Vigna's xoroshiro128+ generator for random number.
 */
#ifndef RANDAMU_XS128_H_
#define RANDAMU_XS128_H_

#include <stdint.h>
#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint64_t state[2];
} rd_xs128;

/**
 * \brief Initializes a xoroshiro128+ generator with a seed and the splitmix64
 *        generator.
 *
 * \param r     The generator to initialize.
 */
void rd_xs128_init(rd_xs128 *r, uint64_t seed);

/**
 * \brief Initializes a xoroshiro128+ generator with a time and the splitmix64
 *        generator.
 *
 * \param r     The generator to initialize.
 */
void rd_xs128_init_time(rd_xs128 *r);

/**
 * \brief Initializes a xoroshiro128+ generator by copying the state of an
 *        existing genereator and making a jump of 2^64 numbers in the sequence.
 *        Can be used 2^64 times (~18 000 000 000 000 000 000) before coming
 *        back to the origin.
 *
 * \param r     The generator to initialize.
 * \param r0    The old generator to jump from.
 */
void rd_xs128_init_jump(rd_xs128 *r, const rd_xs128 *r0);

/**
 * \brief Returns the next 64-bit integer.
 */
uint64_t rd_xs128_next(rd_xs128 *r);

/**
 * \brief Returns the next number in the [0, 1) range.
 */
double rd_xs128_double(rd_xs128 *r);

/**
 * \brief Return a double from the normal distribution.
 *
 * \param r         The generator.
 * \return          A normal random variable.
 */
double rd_xs128_normal(rd_xs128 *r);

/**
 * \brief Generates two numbers in the normal distribution.
 *
 * \param r         The generator.
 * \param n0        Storage for the second normal number.
 * \param n1        Storage for the second normal number.
 */
void rd_xs128_normals(rd_xs128 *r, double *n0, double *n1);

/**
 * \brief Returns a double from the exponential distribution (between 0 and 1).
 *
 * \param r         The generator.
 * \return          An exponential random variable.
 */
double rd_xs128_exp(rd_xs128 *r);

/**
 * \brief Returns an integer from a poisson distribution given lambda.
 *
 * \param r         The generator.
 * \param lambda    The lambda parameter of the poisson distribution.
 * \return          A number in the poisson distribution.
 */
int rd_xs128_poisson(rd_xs128 *r, double lambda);

/**
 * \brief This is the jump function for the generator. It is equivalent
 *        to 2^512 calls to next(); it can be used to generate 2^512
 *        non-overlapping subsequences for parallel computations.
 */
void rd_xs128_jump(rd_xs128 *r);

#ifdef __cplusplus
}
#endif

#endif
