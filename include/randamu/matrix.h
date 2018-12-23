#ifndef RD_MATRIX_rd_
#define RD_MATRIX_rd_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Column-major matrix of single-precision floats.
 */
typedef struct {
  float* data;
  size_t nrows;
  size_t ncols;
} rd_smatrix;

/**
 * \brief Column-major matrix of double-precision floats.
 */
typedef struct {
  double* data;
  size_t nrows;
  size_t ncols;
} rd_dmatrix;

/**
 * \brief Column-major matrix of single-precision complex numbers.
 */
typedef struct {
  float complex* data;
  size_t nrows;
  size_t ncols;
} rd_cmatrix;

/**
 * \brief Column-major matrix of double-precision complex numbers.
 */
typedef struct {
  double complex* data;
  size_t nrows;
  size_t ncols;
} rd_zmatrix;

/**
 * \brief Column-major matrix of 32-bit signed integers.
 */
typedef struct {
  int32_t* data;
  size_t nrows;
  size_t ncols;
} rd_i32matrix;

/**
 * \brief Column-major matrix of 64-bit signed integers.
 */
typedef struct {
  int64_t* data;
  size_t nrows;
  size_t ncols;
} rd_i64matrix;

/**
 * \brief Column-major matrix of 32-bit unsigned integers.
 */
typedef struct {
  uint32_t* data;
  size_t nrows;
  size_t ncols;
} rd_u32matrix;

/**
 * \brief Column-major matrix of 64-bit unsigned integers.
 */
typedef struct {
  uint64_t* data;
  size_t nrows;
  size_t ncols;
} rd_u64matrix;

/**
 * \brief Generic macro to get the total number of elements in the matrix.
 */
#define rd_matrix_size(m)          ((m)->nrows * (m)->ncols)

/**
 * \brief Generic macro to return the number of bytes taken by the matrix's internal array of elements.
 */
#define rd_matrix_sizeof(m)        (rd_matrix_size(m) * sizeof((m)->data[0]))

/**
 * \brief Generic macro to get the element at the given row 'r' and column 'c'.
 */
#define rd_matrix_get(m, r, c)     ((m)->data[(c) * (m)->nrows + (r)])

/**
 * \brief Generic macro, returns true for matrices holding a single element.
 */
#define rd_matrix_is_scalar(m)     ((m)->nrows == 1 && (m)->ncols == 1)

/**
 * \brief Generic macro, returns true for matrices with a single column.
 */
#define rd_matrix_is_colvec(m)     ((m)->ncols == 1)

/**
 * \brief Generic macro, returns true for matrices with a single row.
 */
#define rd_matrix_is_rowvec(m)     ((m)->nrows == 1)

/**
 * \brief Generic macro, returns true for matrices with either a single row or a single column.
 */
#define rd_matrix_is_vector(m)     ((m)->nrows == 1 || (m)->ncols == 1)

/**
 * \brief Initializes a single-precision matrix.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_smatrix_init(rd_smatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a single-precision matrix filled with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_smatrix_init_zeroes(rd_smatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a single-precision matrix and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_smatrix_init_fill(rd_smatrix* m, const size_t nrows, const size_t ncols, const float fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_smatrix_copy(rd_smatrix* dest, const rd_smatrix* src);

/**
 * \brief Frees the memory of a single-precision matrix.
 * \param m       The matrix to free
 */
rd_export void rd_smatrix_free(rd_smatrix* m);

/**
 * \brief Initializes a double-precision matrix.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_dmatrix_init(rd_dmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a double-precision matrix filled with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_dmatrix_init_zeroes(rd_dmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a double-precision matrix and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_dmatrix_init_fill(rd_dmatrix* m, const size_t nrows, const size_t ncols, const double fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_dmatrix_copy(rd_dmatrix* dest, const rd_dmatrix* src);

/**
 * \brief Frees the memory of a double-precision matrix.
 * \param m       The matrix to free
 */
rd_export void rd_dmatrix_free(rd_dmatrix* m);

/**
 * \brief Initializes a single-precision complex matrix.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_cmatrix_init(rd_cmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a single-precision matrix complex filled with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_cmatrix_init_zeroes(rd_cmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a single-precision complex matrix and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_cmatrix_init_fill(rd_cmatrix* m, const size_t nrows, const size_t ncols, const float complex fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_cmatrix_copy(rd_cmatrix* dest, const rd_cmatrix* src);

/**
 * \brief Frees the memory of a single-precision complex matrix.
 * \param m       The matrix to free
 */
rd_export void rd_cmatrix_free(rd_cmatrix* m);

/**
 * \brief Initializes a double-precision complex matrix.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_zmatrix_init(rd_zmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a double-precision complex matrix filled with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_zmatrix_init_zeroes(rd_zmatrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a double-precision complex matrix and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_zmatrix_init_fill(rd_zmatrix* m, const size_t nrows, const size_t ncols, const double complex fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_zmatrix_copy(rd_zmatrix* dest, const rd_zmatrix* src);

/**
 * \brief Frees the memory of a double-precision complex matrix.
 * \param m       The matrix to free
 */
rd_export void rd_zmatrix_free(rd_zmatrix* m);

/**
 * \brief Initializes a matrix of 32-bit signed integers.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_i32matrix_init(rd_i32matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializesa matrix of 32-bit signed integers with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_i32matrix_init_zeroes(rd_i32matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a matrix of 32-bit signed integers and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_i32matrix_init_fill(rd_i32matrix* m, const size_t nrows, const size_t ncols, const int32_t fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_i32matrix_copy(rd_i32matrix* dest, const rd_i32matrix* src);

/**
 * \brief Frees the memory of a matrix of 32-bit signed integers.
 * \param m       The matrix to free
 */
rd_export void rd_i32matrix_free(rd_i32matrix* m);

/**
 * \brief Initializes a matrix of 64-bit signed integers.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_i64matrix_init(rd_i64matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializesa matrix of 64-bit signed integers with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_i64matrix_init_zeroes(rd_i64matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a matrix of 64-bit signed integers and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_i64matrix_init_fill(rd_i64matrix* m, const size_t nrows, const size_t ncols, const int64_t fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_i64matrix_copy(rd_i64matrix* dest, const rd_i64matrix* src);

/**
 * \brief Frees the memory of a matrix of 64-bit signed integers.
 * \param m       The matrix to free
 */
rd_export void rd_i64matrix_free(rd_i64matrix* m);

/**
 * \brief Initializes a matrix of 32-bit unsigned integers.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_u32matrix_init(rd_u32matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializesa matrix of 32-bit unsigned integers with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_u32matrix_init_zeroes(rd_u32matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a matrix of 32-bit unsigned integers and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_u32matrix_init_fill(rd_u32matrix* m, const size_t nrows, const size_t ncols, const uint32_t fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_u32matrix_copy(rd_u32matrix* dest, const rd_u32matrix* src);

/**
 * \brief Frees the memory of a matrix of 32-bit unsigned integers.
 * \param m       The matrix to free
 */
rd_export void rd_u32matrix_free(rd_u32matrix* m);

/**
 * \brief Initializes a matrix of 64-bit unsigned integers.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_u64matrix_init(rd_u64matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializesa matrix of 64-bit unsigned integers with zeroes.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 */
rd_export void rd_u64matrix_init_zeroes(rd_u64matrix* m, const size_t nrows, const size_t ncols);

/**
 * \brief Initializes a matrix of 64-bit unsigned integers and fill it.
 * \param m       Matrix to initialize
 * \param nrows   Number of rows
 * \param ncols   Number of columns
 * \param fill    Value to fill the matrix with
 */
rd_export void rd_u64matrix_init_fill(rd_u64matrix* m, const size_t nrows, const size_t ncols, const uint64_t fill);

/**
 * \brief Performs a deep copy of 'src' to 'dest'.
 * \param dest   The destination (where to copy)
 * \param src    The matrix to copy
 */
rd_export void rd_u64matrix_copy(rd_u64matrix* dest, const rd_u64matrix* src);

/**
 * \brief Frees the memory of a matrix of 64-bit unsigned integers.
 * \param m       The matrix to free
 */
rd_export void rd_u64matrix_free(rd_u64matrix* m);

#ifdef __cplusplus
}
#endif

#endif
