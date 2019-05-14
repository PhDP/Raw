#include "randamu/matrix.h"

#define RANDAMU_GENERATE_MATRIX_DEF(NAME, SCALAR) void NAME ## _init(NAME* m, const size_t nrows, const size_t \
      ncols) { \
    m->data = (SCALAR*)realloc((void*)m->data, nrows * ncols * sizeof(SCALAR)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
  } \
  \
  void NAME ## _init_zeroes(NAME* m, const size_t nrows, \
      const size_t ncols) { \
    m->data = (SCALAR*)calloc(nrows * ncols, sizeof(SCALAR)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
  } \
  \
  void NAME ## _init_fill(NAME* m, const size_t nrows, \
      const size_t ncols, const SCALAR fill) { \
    const size_t nelems = nrows * ncols; \
    m->data = (SCALAR*)realloc((void*)m->data, nelems * sizeof(SCALAR)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
    size_t i = 0; \
    for (; i < nelems; ++i) { \
      m->data[i] = fill; \
    } \
  } \
  \
  void NAME ## _copy(NAME* dest, const NAME* src) { \
    const size_t bytes = src->nrows * src->ncols * sizeof(SCALAR); \
    dest->data = (SCALAR*)realloc((void*)dest->data, bytes); \
    dest->nrows = src->nrows; \
    dest->ncols = src->ncols; \
    memcpy((void*)dest->data, (const void*)src->data, bytes); \
  } \
  \
  void NAME ## _free(NAME* m) { \
    if (m) { \
      if (m->data) { \
        free(m->data); \
      } \
      m->nrows = 0; \
      m->ncols = 0; \
    } \
  }

RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_f32, float)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_f64, double)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_c32, float complex)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_c64, double complex)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_i32, int32_t)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_i64, int64_t)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_u32, uint32_t)
RANDAMU_GENERATE_MATRIX_DEF(rd_matrix_u64, uint64_t)
