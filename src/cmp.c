#include "raw/cmp.h"

// Generates definitions for many ascending and descending comparison functions
#define RAW_GENERATE_CMP_DEF(NAME, TNAME) \
  int r_cmp_ ## NAME ## _asc(const void* lhs, const void* rhs) { \
    if (*(const TNAME*)lhs < *(const TNAME*)rhs) { \
      return -1; \
    } \
    return *(const TNAME*)lhs != *(const TNAME*)rhs; \
  } \
  \
  int r_cmp_ ## NAME ## _des(const void* lhs, const void* rhs) { \
    if (*(const TNAME*)lhs > *(const TNAME*)rhs) { \
      return -1; \
    } \
    return *(const TNAME*)lhs != *(const TNAME*)rhs; \
  }

#define RAW_GENERATE_CMP_ARR(NAME, TNAME) \
  int r_cmp_ ## NAME ## _arr(const TNAME* lhs, const TNAME* rhs, const size_t n) { \
    size_t i = 0; \
    for (; i < n; ++i) { \
      if (lhs[i] < rhs[i]) { \
        return -1; \
      } else if (rhs[i] < lhs[i]) { \
        return 1; \
      } \
    } \
    return 0; \
  }

int r_cmp_str_asc(const void* lhs, const void* rhs) {
  return strcmp(*(const char**)lhs, *(const char**)rhs);
}

int r_cmp_str_des(const void *lhs, const void *rhs) {
  return -strcmp(*(const char**)lhs, *(const char**)rhs);
}

RAW_GENERATE_CMP_DEF(c, char)
RAW_GENERATE_CMP_DEF(f32, float)
RAW_GENERATE_CMP_DEF(f64, double)
RAW_GENERATE_CMP_DEF(i, int)
RAW_GENERATE_CMP_DEF(u, unsigned int)
RAW_GENERATE_CMP_DEF(l, long)
RAW_GENERATE_CMP_DEF(lu, unsigned long)
RAW_GENERATE_CMP_DEF(sz, size_t)
RAW_GENERATE_CMP_DEF(i8, int8_t)
RAW_GENERATE_CMP_DEF(i16, int16_t)
RAW_GENERATE_CMP_DEF(i32, int32_t)
RAW_GENERATE_CMP_DEF(i64, int64_t)
RAW_GENERATE_CMP_DEF(u8, uint8_t)
RAW_GENERATE_CMP_DEF(u16, uint16_t)
RAW_GENERATE_CMP_DEF(u32, uint32_t)
RAW_GENERATE_CMP_DEF(u64, uint64_t)

RAW_GENERATE_CMP_ARR(f32, float)
RAW_GENERATE_CMP_ARR(f64, double)
