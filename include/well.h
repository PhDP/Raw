/*! \file
 *
 * \brief The well random number generator, based on: P L'Ecuyer,
 * F Panneton, and M Matsumoto. Improved Long-Period Generators Based on Linear
 * Recurrences Modulo 2.
 */

#pragma once

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * \brief The state of a well random number generator.
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
} well;

/**
 * \brief Julienne Walker's portable function (from www.eternallyconfuzzled.com)
 * to get an unsigned int from time().
 *
 * Warning: on most systems it will return the same value if called twice within
 * one second.
 *
 * \return          An unsigned integer derived from time()
 */
unsigned int time_seed();

/**
 * \brief Seed a well generator with an unsigned integer.
 *
 * \param rng       The generator.
 * \param seed      The seed used to initialize the generator.
 */
void well_init(well *rng, unsigned int seed);

/**
 * \brief Initialize with time using time_seed().
 *
 * \param rng       The generator.
 * \return          The seed used.
 */
unsigned int well_init_time(well *rng);

/**
 * \brief Return a double in the [0, 1) uniform range.
 *
 * This is the 'native' generator: all other random numbers (normal,
 * exponential, integers, ...) use this function.
 *
 * \param rng       The generator
 * \return          A random value in the [0, 1) uniform range.
 */
double well_double(well *rng);

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
#define well_int(rng,b)   ((int)(well_double(rng)*(b)))

/**
 * \brief Return an unsigned integer in the [0, b) uniform range (including 0,
 * excluding b).
 *
 * \param rng       The generator
 * \param b         Upper limit: the highest possible value is b - 1
 * \return          A random interger in the [0, b) uniform range.
 */
#define well_uint(rng,b)   ((unsigned int)(well_double(rng)*(b)))

/**
 * \brief Return an integer in the [0, MAX) range, where MAX is the
 * highest possible value for an integer.
 *
 * \param rng       The generator
 * \return          A random interger in the [0, MAX) uniform range.
 */
#define well_int_max(rng)   ((int)(well_double(rng)*INT32_MAX))

/**
 * \brief Return an unsigned integer in the [0, MAX) range, where MAX is the
 * highest possible value for an integer.
 *
 * \param rng       The generator
 * \return          A random interger in the [0, MAX) uniform range.
 */
#define well_uint_max(rng)  ((unsigned int)(well_double(rng)*UINT32_MAX))

/**
 * \brief Return a double from the normal distribution.
 *
 * \param rng       The generator
 * \return          An exponential random variable.
 */
double well_normal(well *rng);

/**
 * \brief Generates two normal numbers.
 *
 * \param rng       The generator
 * \param normal0   Where to store the first normal number.
 * \param normal1   Where to store the second normal number.
 */
void well_normal2(well *rng, double *normal0, double *normal1);

/**
 * \brief Return a double from the exponential distribution (between 0 and 1).
 *
 * \param rng       The generator
 * \return          An exponential random variable.
 */
double well_exp(well *rng);

/**
 * \brief Return an integer from a poisson distribution given lambda.
 *
 * \param rng       The generator
 * \param lambda    The lambda parameter of the poisson distribution.
 * \return          A number in the poisson distribution.
 */
int well_poisson(well *rng, double lambda);

#ifdef __cplusplus
}
#endif
