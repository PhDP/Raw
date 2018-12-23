#include "randamu/matrix.h"

#define MATRIX_INIT(name, scalar) void name ## _init(name* m, const size_t nrows, const size_t \
      ncols) { \
    m->data = (scalar*)realloc((void*)m->data, nrows * ncols * sizeof(scalar)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
  }

#define MATRIX_INIT_ZEROES(name, scalar) void name ## _init_zeroes(name* m, const size_t nrows, \
      const size_t ncols) { \
    m->data = (scalar*)calloc(nrows * ncols, sizeof(scalar)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
  }

#define MATRIX_INIT_FILL(name, scalar) void name ## _init_fill(name* m, const size_t nrows, \
      const size_t ncols, const scalar fill) { \
    const size_t nelems = nrows * ncols; \
    m->data = (scalar*)realloc((void*)m->data, nelems * sizeof(scalar)); \
    m->nrows = nrows; \
    m->ncols = ncols; \
    size_t i = 0; \
    for (; i < nelems; ++i) { \
      m->data[i] = fill; \
    } \
  }

#define MATRIX_COPY(name, scalar) void name ## _copy(name* dest, const name* src) { \
    const size_t bytes = src->nrows * src->ncols * sizeof(scalar); \
    dest->data = (scalar*)realloc((void*)dest->data, bytes); \
    dest->nrows = src->nrows; \
    dest->ncols = src->ncols; \
    memcpy((void*)dest->data, (const void*)src->data, bytes); \
  }

#define MATRIX_FREE(name) void name ## _free(name* m) { \
    if (m) { \
      if (m->data) { \
        free(m->data); \
      } \
      m->nrows = 0; \
      m->ncols = 0; \
    } \
  }

MATRIX_INIT(rd_smatrix, float)
MATRIX_INIT_ZEROES(rd_smatrix, float)
MATRIX_INIT_FILL(rd_smatrix, float)
MATRIX_COPY(rd_smatrix, float)
MATRIX_FREE(rd_smatrix)

MATRIX_INIT(rd_dmatrix, double)
MATRIX_INIT_ZEROES(rd_dmatrix, double)
MATRIX_INIT_FILL(rd_dmatrix, double)
MATRIX_COPY(rd_dmatrix, double)
MATRIX_FREE(rd_dmatrix)

MATRIX_INIT(rd_cmatrix, float complex)
MATRIX_INIT_ZEROES(rd_cmatrix, float complex)
MATRIX_INIT_FILL(rd_cmatrix, float complex)
MATRIX_COPY(rd_cmatrix, float complex)
MATRIX_FREE(rd_cmatrix)

MATRIX_INIT(rd_zmatrix, double complex)
MATRIX_INIT_ZEROES(rd_zmatrix, double complex)
MATRIX_INIT_FILL(rd_zmatrix, double complex)
MATRIX_COPY(rd_zmatrix, double complex)
MATRIX_FREE(rd_zmatrix)

MATRIX_INIT(rd_i32matrix, int32_t)
MATRIX_INIT_ZEROES(rd_i32matrix, int32_t)
MATRIX_INIT_FILL(rd_i32matrix, int32_t)
MATRIX_COPY(rd_i32matrix, int32_t)
MATRIX_FREE(rd_i32matrix)

MATRIX_INIT(rd_i64matrix, int64_t)
MATRIX_INIT_ZEROES(rd_i64matrix, int64_t)
MATRIX_INIT_FILL(rd_i64matrix, int64_t)
MATRIX_COPY(rd_i64matrix, int64_t)
MATRIX_FREE(rd_i64matrix)

MATRIX_INIT(rd_u32matrix, uint32_t)
MATRIX_INIT_ZEROES(rd_u32matrix, uint32_t)
MATRIX_INIT_FILL(rd_u32matrix, uint32_t)
MATRIX_COPY(rd_u32matrix, uint32_t)
MATRIX_FREE(rd_u32matrix)

MATRIX_INIT(rd_u64matrix, uint64_t)
MATRIX_INIT_ZEROES(rd_u64matrix, uint64_t)
MATRIX_INIT_FILL(rd_u64matrix, uint64_t)
MATRIX_COPY(rd_u64matrix, uint64_t)
MATRIX_FREE(rd_u64matrix)
