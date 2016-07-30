#include "randamu/splitmix64.h"

uint64_t rd_splitmix64(uint64_t seed) {
  uint64_t z = (seed += UINT64_C(0x9E3779B97F4A7C15));
  z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
  z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
  return z ^ (z >> 31);
}

void rd_splitmix64_arr(uint64_t seed, uint64_t *arr, size_t size) {
  while (size-- > 0) {
    seed = rd_splitmix64(seed);
    *arr++ = seed;
  }
}
