/*! \file
  \brief xorshift128 algorithm
 */
#ifndef RANDAMU_XORSHIFT128_H_
#define RANDAMU_XORSHIFT128_H_

#include <stdint.h>
#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint64_t state[2];
} rd_xs128;

void rd_xs128_init(rd_xs128 *r, uint64_t seed);

/**
  \brief This is the jump function for the generator. It is equivalent
         to 2^512 calls to next(); it can be used to generate 2^512
         non-overlapping subsequences for parallel computations.
 */
void rd_xs128_jump(rd_xs128 *r);

uint64_t rd_xs128_next(rd_xs128 *r);

double rd_xs128_double(rd_xs128 *r);

#ifdef __cplusplus
}
#endif

#endif
