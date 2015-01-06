/*! \file
 *
 * \brief The rd_rng random number generator, based on: P L'Ecuyer,
 * F Panneton, and M Matsumoto. Improved Long-Period Generators Based on Linear
 * Recurrences Modulo 2.
 */

#ifndef RD_RNG_H_
#define RD_RNG_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief The state of a rd_rng random number generator.
 */
typedef struct {
  /**
   * \brief Internal state of the generator.
   */
  uint32_t state[32];
  /**
   * \brief Internal state of the generator.
   */
  uint32_t state_n;
  /**
   * \brief The initial seed used to initiate the generator.
   */
  uint32_t seed;
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
 * to get an uint32_t from time().
 *
 * Warning: on most systems it will return the same value if called twice within
 * one second.
 *
 * \return          An uint32_teger derived from time()
 */
uint32_t rd_time_seed();

/**
 * \brief Seed a rd_rng generator with an uint32_teger.
 *
 * \param rng       The generator.
 * \param seed      The seed used to initialize the generator.
 * \return          Returns the seed used.
 */
uint32_t rd_rng_init(rd_rng *r, uint32_t seed);

/**
 * \brief Initialize with time using time_seed().
 *
 * \param rng       The generator.
 * \return          The seed used.
 */
uint32_t rd_rng_init_time(rd_rng *r);

/**
 * \brief Return a double in the [0, 1) uniform range.
 *
 * \param rng       The generator
 * \return          A random value in the [0, 1) uniform range.
 */
double rd_rng_double(rd_rng *r);

/**
 * \brief Returns a number in the [0, 4294967296] range.
 *
 * \param rng       The generator
 * \return          A random value in the [0, 4294967296] uniform range.
 */
uint32_t rd_rng_uint(rd_rng *r);

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
#define rd_rng_intb(r, b) ((int)(rd_rng_double(r) * (b)))

/**
 * \brief Return an uint32_teger in the [0, b) uniform range (including 0,
 * excluding b).
 *
 * \param rng       The generator
 * \param b         Upper limit: the highest possible value is b - 1
 * \return          A random interger in the [0, b) uniform range.
 */
#define rd_rng_uintb(r, b) ((uint32_t)(rd_rng_double(r) * (b)))

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

/** 
 * \brief Allocates a random block of memory.
 */
void * randalloc(rd_rng *r, size_t size);

#ifdef __cplusplus
}
#endif

#endif
