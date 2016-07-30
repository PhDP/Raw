#include "randamu/splitmix64.h"
#include "randamu/xorshift1024.h"

void rd_xs1024_init(rd_xs1024 *r, uint64_t seed) {
  rd_splitmix64_arr(seed, r->state, 16);
  r->p = 0;
}

uint64_t rd_xs1024_next(rd_xs1024 *r) {
  const uint64_t s0 = r->state[r->p];
  uint64_t s1 = r->state[r->p = (r->p + 1) & 15];
  s1 ^= s1 << 31; // a
  r->state[r->p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b, c
  return r->state[r->p] * UINT64_C(1181783497276652981);
}

double rd_xs1024_double(rd_xs1024 *r) {
  const union { uint64_t i; double d; } u = {
    .i = UINT64_C(0x3FF) << 52 | rd_xs1024_next(r) >> 12
  };
  return u.d - 1.0;
}

void rd_xs1024_jump(rd_xs1024 *r) {
  static const uint64_t JUMP[] = { 0x84242f96eca9c41d,
    0xa3c65b8776f96855, 0x5b34a39f070b5837, 0x4489affce4f31a1e,
    0x2ffeeb0a48316f40, 0xdc2d9891fe68c022, 0x3659132bb12fea70,
    0xaac17d8efa43cab8, 0xc4cb815590989b13, 0x5ee975283d71c93b,
    0x691548c86c1bd540, 0x7910c41d10a1e6a5, 0x0b5fc64563b3e2a8,
    0x047f7684e9fc949d, 0xb99181f2d8f685ca, 0x284600e3f30e38c3
  };

  uint64_t t[16] = { 0 };
  int i, b, j;
  for (i = 0; i < sizeof JUMP / sizeof *JUMP; ++i) {
    for (b = 0; b < 64; ++b) {
      if (JUMP[i] & 1ULL << b) {
        for (j = 0; j < 16; ++j) {
          t[j] ^= r->state[(j + r->p) & 15];
        }
      }
      rd_xs1024_next(r);
    }
  }
  for (j = 0; j < 16; j++) {
    r->state[(j + r->p) & 15] = t[j];
  }
}
