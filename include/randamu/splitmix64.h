/*! \file
 *
 * \brief Sebastiano Vigna's simple random number generator used to seed
 *        xorshift.
 */
#ifndef RANDAMU_SPLITMIX64_H_
#define RANDAMU_SPLITMIX64_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Returns a random number with the splitmix64 algorithm.
 */
uint64_t rd_splitmix64(uint64_t n);

/**
 * \brief Fills an array of random numbers with the splitmix64 algorithm.
 *
 * \param  seed    Initial number to seed the random number generator.
 * \param  arr     Array to be filled.
 * \param  nmemb   Number of elements in the array.
 */
void rd_splitmix64_arr(uint64_t seed, uint64_t *arr, size_t nmemb);

#ifdef __cplusplus
}
#endif

#endif
