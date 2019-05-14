#include "randamu/cmp.h"

// Generates definitions for many ascending and descending comparison functions
#define RANDAMU_GENERATE_CMP_DEF(NAME, TNAME) \
  int rd_cmp_ ## NAME ## _asc(const void* lhs, const void* rhs) { \
    if (*(const TNAME*)lhs < *(const TNAME*)rhs) { \
      return -1; \
    } \
    return *(const TNAME*)lhs != *(const TNAME*)rhs; \
  } \
  \
  int rd_cmp_ ## NAME ## _des(const void* lhs, const void* rhs) { \
    if (*(const TNAME*)lhs > *(const TNAME*)rhs) { \
      return -1; \
    } \
    return *(const TNAME*)lhs != *(const TNAME*)rhs; \
  }

int rd_cmp_str_asc(const void* lhs, const void* rhs) {
  return strcmp(*(const char**)lhs, *(const char**)rhs);
}

int rd_cmp_str_des(const void *lhs, const void *rhs) {
  return -strcmp(*(const char**)lhs, *(const char**)rhs);
}

RANDAMU_GENERATE_CMP_DEF(c, char)
RANDAMU_GENERATE_CMP_DEF(f32, float)
RANDAMU_GENERATE_CMP_DEF(f64, double)
RANDAMU_GENERATE_CMP_DEF(i, int)
RANDAMU_GENERATE_CMP_DEF(u, unsigned int)
RANDAMU_GENERATE_CMP_DEF(l, long)
RANDAMU_GENERATE_CMP_DEF(lu, unsigned long)
RANDAMU_GENERATE_CMP_DEF(sz, size_t)
RANDAMU_GENERATE_CMP_DEF(i8, int8_t)
RANDAMU_GENERATE_CMP_DEF(i16, int16_t)
RANDAMU_GENERATE_CMP_DEF(i32, int32_t)
RANDAMU_GENERATE_CMP_DEF(i64, int64_t)
RANDAMU_GENERATE_CMP_DEF(u8, uint8_t)
RANDAMU_GENERATE_CMP_DEF(u16, uint16_t)
RANDAMU_GENERATE_CMP_DEF(u32, uint32_t)
RANDAMU_GENERATE_CMP_DEF(u64, uint64_t)
