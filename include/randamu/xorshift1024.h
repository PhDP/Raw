/*! \file
  \brief xorshift1014* algorithm
 */
#ifndef RANDAMU_XORSHIFT1024_RNG_H_
#define RANDAMU_XORSHIFT1024_RNG_H_

#include <stdint.h>
#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint64_t state[16];
  int p; // size_t p???
} rd_xs1024;

void rd_xs1024_init(rd_xs1024 *r, uint64_t seed);

/**
  \brief This is the jump function for the generator. It is equivalent
         to 2^512 calls to next(); it can be used to generate 2^512
         non-overlapping subsequences for parallel computations.
 */
void rd_xs1024_jump(rd_xs1024 *r);

uint64_t rd_xs1024_next(rd_xs1024 *r);

double rd_xs1024_double(rd_xs1024 *r);

#ifdef __cplusplus
}
#endif

#endif
