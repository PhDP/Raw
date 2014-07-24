/*! \file
 *
 * \brief The rd_rng random number generator, based on: P L'Ecuyer,
 * F Panneton, and M Matsumoto. Improved Long-Period Generators Based on Linear
 * Recurrences Modulo 2.
 */

// clang -std=c99 test_random_seq.c -I../headers -o test -lm

#ifndef RD_RNG_H_
#define RD_RNG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * \brief The state of a rd_rng random number generator.
 */
typedef struct {
  /**
   * \brief Internal state of the generator.
   */
  unsigned int state[32];
  /**
   * \brief Internal state of the generator.
   */
  unsigned int state_n;
  /**
   * \brief The initial seed used to initiate the generator.
   */
  unsigned int seed;
  /**
   * \brief Has a next double.
   */
  bool has_next;
  /**
   * \brief Next double.
   */
  double next_normal;
} rd_rng;

/**
 * \brief Julienne Walker's portable function (from www.eternallyconfuzzled.com)
 * to get an unsigned int from time().
 *
 * Warning: on most systems it will return the same value if called twice within
 * one second.
 *
 * \return          An unsigned integer derived from time()
 */
unsigned int rd_time_seed();

/**
 * \brief Seed a rd_rng generator with an unsigned integer.
 *
 * \param rng       The generator.
 * \param seed      The seed used to initialize the generator.
 * \return          Returns the seed used.
 */
unsigned int rd_rng_init(rd_rng *r, unsigned int seed);

/**
 * \brief Initialize with time using time_seed().
 *
 * \param rng       The generator.
 * \return          The seed used.
 */
unsigned int rd_rng_init_time(rd_rng *r);

/**
 * \brief Return a double in the [0, 1) uniform range.
 *
 * This is the 'native' generator: all other random numbers (normal,
 * exponential, integers, ...) use this function.
 *
 * \param rng       The generator
 * \return          A random value in the [0, 1) uniform range.
 */
double rd_rng_double(rd_rng *r);

/**
 * \brief Return an integer in the [0, b) uniform range (including 0, excluding
 * b).
 *
 * Bechmarks show ~5% performane improvement over a normal function, which
 * is enough to justify the define for such procedure.
 *
 * \param rng       The generator
 * \param b         Upper limit: the highest possible value is b - 1
 * \return          A random interger in the [0, b) uniform range.
 */
#define rd_rng_int(r, b) ((int)(rd_rng_double(r) * (b)))

/**
 * \brief Return an unsigned integer in the [0, b) uniform range (including 0,
 * excluding b).
 *
 * \param rng       The generator
 * \param b         Upper limit: the highest possible value is b - 1
 * \return          A random interger in the [0, b) uniform range.
 */
#define rd_rng_uint(r, b) ((unsigned int)(rd_rng_double(r) * (b)))

/**
 * \brief Return an integer in the [0, MAX) range, where MAX is the
 * highest possible value for an integer.
 *
 * \param rng       The generator
 * \return          A random interger in the [0, MAX) uniform range.
 */
#define rd_rng_int_max(r) ((int)(rd_rng_double(r) * INT32_MAX))

/**
 * \brief Return an unsigned integer in the [0, MAX) range, where MAX is the
 * highest possible value for an integer.
 *
 * \param rng       The generator
 * \return          A random interger in the [0, MAX) uniform range.
 */
#define rd_rng_uint_max(r) ((unsigned int)(rd_rng_double(r) * UINT32_MAX))

/**
 * \brief Return a double from the normal distribution.
 *
 * \param rng       The generator
 * \return          An exponential random variable.
 */
double rd_rng_normal(rd_rng *r);

/**
 * \brief Returns a double from the exponential distribution (between 0 and 1).
 *
 * \param rng       The generator
 * \return          An exponential random variable.
 */
double rd_rng_exp(rd_rng *r);

/**
 * \brief Returns an integer from a poisson distribution given lambda.
 *
 * \param rng       The generator
 * \param lambda    The lambda parameter of the poisson distribution.
 * \return          A number in the poisson distribution.
 */
int rd_rng_poisson(rd_rng *r, double lambda);

#ifdef __cplusplus
}
#endif

#endif
