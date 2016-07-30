#include <time.h>
#include <math.h>
#include "randamu/xorshift128.h"
#include "randamu/splitmix64.h"

// macro?

static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

void rd_xs128_init(rd_xs128 *r, uint64_t seed) {
  r->state[0] = rd_splitmix64(seed);
  r->state[1] = rd_splitmix64(r->state[0]);
}

void rd_xs128_init_time(rd_xs128 *r) {
  r->state[0] = rd_splitmix64(time(NULL));
  r->state[1] = rd_splitmix64(r->state[0]);
}

uint64_t rd_xs128_next(rd_xs128 *r) {
  const uint64_t s0 = r->state[0];
  uint64_t s1 = r->state[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  r->state[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
  r->state[1] = rotl(s1, 36);

  return result;
}

double rd_xs128_double(rd_xs128 *r) {
  const union { uint64_t i; double d; } u = {
    .i = UINT64_C(0x3FF) << 52 | rd_xs128_next(r) >> 12
  };
  return u.d - 1.0;
}

double rd_xs128_normal(rd_xs128 *r) {
  double n0, n1, s;
  do {
    n0 = 2.0 * rd_xs128_double(r) - 1.0;
    n1 = 2.0 * rd_xs128_double(r) - 1.0;
    s = n0 * n0 + n1 * n1;
  } while (s >= 1 || s == 0);
  return n0 * sqrt(-2.0 * log(s) / s);
}

int rd_xs128_poisson(rd_xs128 *r, double lambda) {
  const double l = pow(2.71828182845904523536, -lambda);
  double p = 1.0;
  int k = 0;
  do {
    ++k;
    p *= rd_xs128_double(r);
  } while (p > l);
  return k - 1;
}

double rd_xs128_exp(rd_xs128 *r) {
  double x = rd_xs128_double(r);
  while (x == 0.0)
    x = rd_xs128_double(r);
  return -log(x);
}

void rd_xs128_jump(rd_xs128 *r) {
  static const uint64_t JUMP[] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

  uint64_t s0 = 0, s1 = 0;
  int i, b;
  for (i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
    for (b = 0; b < 64; b++) {
      if (JUMP[i] & 1ULL << b) {
        s0 ^= r->state[0];
        s1 ^= r->state[1];
      }
      rd_xs128_next(r);
    }
  }
  r->state[0] = s0;
  r->state[1] = s1;
}
