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

void rd_xs128_jump(rd_xs128 *r) {
  static const uint64_t JUMP[] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

  uint64_t s0 = 0, s1 = 0;
  for (int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
    for (int b = 0; b < 64; b++) {
      if (JUMP[i] & 1ULL << b) {
        s0 ^= r->state[0];
        s1 ^= r->state[1];
      }
      rd_xs128_next(r);
    }
  r->state[0] = s0;
  r->state[1] = s1;
}
