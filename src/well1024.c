#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "randamu/well1024.h"

// From Julienne Walker.
uint32_t rd_time_seed() {
  time_t now = time(0);
  unsigned char *p = (unsigned char*)&now;
  uint32_t seed = 0;
  // Knuth's method (TAOCP vol 2).
  size_t i = 0;
  for (; i < sizeof(now); ++i)
    seed = seed * (UCHAR_MAX + 2U) + p[i];
  return seed;
}

uint32_t rd_well1024_init(rd_well1024 *r, uint32_t seed) {
  if (seed == 0)
    seed = 42;
  r->state_n = 0;
  r->state[0] = seed & 0xffffffffU;
  r->has_next = false;
  r->seed = seed;

  int i = 1;
  for (; i < 32; ++i)
    r->state[i] = (69069 * r->state[i - 1]) & 0xffffffffU;

  return seed;
}

uint32_t rd_well1024_init_time(rd_well1024 *r) {
  return rd_well1024_init(r, rd_time_seed());
}

#define RD_MAT3POS(t, v) ((v) ^ ((v) >> (t)))
#define RD_MAT3NEG(t, v) ((v) ^ ((v) << (-t)))
#define RD_IDEN(v) (v)
#define WELL1024_CORE do \
  { \
    const uint32_t state_n = r->state_n; \
    const uint32_t z1 = RD_IDEN(state[state_n]) ^ \
                        RD_MAT3POS(8, state[(state_n + 3) & 0x0000001fUL]); \
    const uint32_t z2 = \
      RD_MAT3NEG((-19), state[(state_n + 24) & 0x0000001fUL]) ^ \
      RD_MAT3NEG((-14), state[(state_n + 10) & 0x0000001fUL]); \
    state[state_n] = z1 ^ z2; \
    state[(state_n + 31) & 0x0000001fUL] = \
      RD_MAT3NEG((-11), (state[(state_n + 31) & 0x0000001fUL])) ^ \
      RD_MAT3NEG((-7), z1) ^ RD_MAT3NEG((-13), z2); \
    r->state_n = (state_n + 31) & 0x0000001fUL; \
  } while (0)

uint32_t rd_well1024_uint(rd_well1024 *r) {
  uint32_t *const state = r->state;
  WELL1024_CORE;
  return state[r->state_n];
}

double rd_well1024_double(rd_well1024 *r) {
  uint32_t *const state = r->state;
  WELL1024_CORE;
  return state[r->state_n] * 2.32830643653869628906e-10;
}

double rd_well1024_normal(rd_well1024 *r) {
  double n0, n1, s;
  do {
    n0 = 2.0 * rd_well1024_double(r) - 1.0;
    n1 = 2.0 * rd_well1024_double(r) - 1.0;
    s = n0 * n0 + n1 * n1;
  } while (s >= 1 || s == 0);
  return n0 * sqrt(-2.0 * log(s) / s);
}

void * rd_randalloc(rd_well1024 *r, size_t size) {
  if (size < 1) {
    return NULL;
  }
  void * base = malloc(size);
  uint8_t * p = (uint8_t *)base;
  if (p == NULL) {
    return NULL;
  }
  const uint8_t * stop = p + size;
  size_t rem = size % sizeof(uint32_t);
  while (rem-- > 0) {
    *p = (uint8_t)rd_well1024_uint(r);
    p += sizeof(uint8_t);
  }
  while (p != stop) {
    *((uint32_t*)p) = rd_well1024_uint(r);
    p += sizeof(uint32_t);
  }
  return base;
}

int rd_well1024_poisson(rd_well1024 *r, double lambda) {
  const double l = pow(2.71828182845904523536, -lambda);
  double p = 1.0;
  int k = 0;
  do {
    ++k;
    p *= rd_well1024_double(r);
  } while (p > l);
  return k - 1;
}

double rd_well1024_exp(rd_well1024 *r) {
  double x = rd_well1024_double(r);
  while (x == 0.0) {
    x = rd_well1024_double(r);
  }
  return -log(x);
}
