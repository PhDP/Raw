/**
 * @file matrix.h
 * @brief Defines column-major matrixes of various types.
 */
#ifndef RANDAMU_MATRIX_H_
#define RANDAMU_MATRIX_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Column-major matrix of single-precision floats.
 */
typedef struct {
  float* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_f32;

/**
 * @brief Column-major matrix of double-precision floats.
 */
typedef struct {
  double* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_f64;

/**
 * @brief Column-major matrix of single-precision complex numbers.
 */
typedef struct {
  float complex* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_c32;

/**
 * @brief Column-major matrix of double-precision complex numbers.
 */
typedef struct {
  double complex* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_c64;

/**
 * @brief Column-major matrix of 32-bit signed integers.
 */
typedef struct {
  int32_t* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_i32;

/**
 * @brief Column-major matrix of 64-bit signed integers.
 */
typedef struct {
  int64_t* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_i64;

/**
 * @brief Column-major matrix of 32-bit unsigned integers.
 */
typedef struct {
  uint32_t* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_u32;

/**
 * @brief Column-major matrix of 64-bit unsigned integers.
 */
typedef struct {
  uint64_t* data;
  size_t nrows;
  size_t ncols;
} rd_matrix_u64;

/**
 * @brief Generic macro to get the total number of elements in the matrix.
 */
#define rd_matrix_size(m)          ((m)->nrows * (m)->ncols)

/**
 * @brief Generic macro to return the number of bytes taken by the matrix's internal array of elements.
 */
#define rd_matrix_sizeof(m)        (rd_matrix_size(m) * sizeof((m)->data[0]))

/**
 * @brief Generic macro to get the element at the given row 'r' and column 'c'.
 */
#define rd_matrix_get(m, r, c)     ((m)->data[(c) * (m)->nrows + (r)])

/**
 * @brief Generic macro, returns true for matrices holding a single element.
 */
#define rd_matrix_is_scalar(m)     ((m)->nrows == 1 && (m)->ncols == 1)

/**
 * @brief Generic macro, returns true for matrices with a single column.
 */
#define rd_matrix_is_colvec(m)     ((m)->ncols == 1)

/**
 * @brief Generic macro, returns true for matrices with a single row.
 */
#define rd_matrix_is_rowvec(m)     ((m)->nrows == 1)

/**
 * @brief Generic macro, returns true for matrices with either a single row or a single column.
 */
#define rd_matrix_is_vector(m)     ((m)->nrows == 1 || (m)->ncols == 1)

/**
 * @brief Initializes a single-precision matrix.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_f32_init(rd_matrix_f32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a single-precision matrix filled with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_f32_init_zeroes(rd_matrix_f32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a single-precision matrix and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_f32_init_fill(rd_matrix_f32* m, const size_t nrows, const size_t ncols, const float fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_f32_copy(rd_matrix_f32* dest, const rd_matrix_f32* src);

/**
 * @brief Frees the memory of a single-precision matrix.
 * @param m       The matrix to free
 */
void rd_matrix_f32_free(rd_matrix_f32* m);

/**
 * @brief Initializes a double-precision matrix.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_f64_init(rd_matrix_f64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a double-precision matrix filled with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_f64_init_zeroes(rd_matrix_f64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a double-precision matrix and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_f64_init_fill(rd_matrix_f64* m, const size_t nrows, const size_t ncols, const double fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_f64_copy(rd_matrix_f64* dest, const rd_matrix_f64* src);

/**
 * @brief Frees the memory of a double-precision matrix.
 * @param m       The matrix to free
 */
void rd_matrix_f64_free(rd_matrix_f64* m);

/**
 * @brief Initializes a single-precision complex matrix.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_c32_init(rd_matrix_c32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a single-precision matrix complex filled with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_c32_init_zeroes(rd_matrix_c32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a single-precision complex matrix and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_c32_init_fill(rd_matrix_c32* m, const size_t nrows, const size_t ncols, const float complex fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_c32_copy(rd_matrix_c32* dest, const rd_matrix_c32* src);

/**
 * @brief Frees the memory of a single-precision complex matrix.
 * @param m       The matrix to free
 */
void rd_matrix_c32_free(rd_matrix_c32* m);

/**
 * @brief Initializes a double-precision complex matrix.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_c64_init(rd_matrix_c64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a double-precision complex matrix filled with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_c64_init_zeroes(rd_matrix_c64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a double-precision complex matrix and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_c64_init_fill(rd_matrix_c64* m, const size_t nrows, const size_t ncols, const double complex fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_c64_copy(rd_matrix_c64* dest, const rd_matrix_c64* src);

/**
 * @brief Frees the memory of a double-precision complex matrix.
 * @param m       The matrix to free
 */
void rd_matrix_c64_free(rd_matrix_c64* m);

/**
 * @brief Initializes a matrix of 32-bit signed integers.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_i32_init(rd_matrix_i32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializesa matrix of 32-bit signed integers with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_i32_init_zeroes(rd_matrix_i32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a matrix of 32-bit signed integers and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_i32_init_fill(rd_matrix_i32* m, const size_t nrows, const size_t ncols, const int32_t fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_i32_copy(rd_matrix_i32* dest, const rd_matrix_i32* src);

/**
 * @brief Frees the memory of a matrix of 32-bit signed integers.
 * @param m       The matrix to free
 */
void rd_matrix_i32_free(rd_matrix_i32* m);

/**
 * @brief Initializes a matrix of 64-bit signed integers.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_i64_init(rd_matrix_i64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializesa matrix of 64-bit signed integers with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_i64_init_zeroes(rd_matrix_i64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a matrix of 64-bit signed integers and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_i64_init_fill(rd_matrix_i64* m, const size_t nrows, const size_t ncols, const int64_t fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_i64_copy(rd_matrix_i64* dest, const rd_matrix_i64* src);

/**
 * @brief Frees the memory of a matrix of 64-bit signed integers.
 * @param m       The matrix to free
 */
void rd_matrix_i64_free(rd_matrix_i64* m);

/**
 * @brief Initializes a matrix of 32-bit unsigned integers.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_u32_init(rd_matrix_u32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializesa matrix of 32-bit unsigned integers with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_u32_init_zeroes(rd_matrix_u32* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a matrix of 32-bit unsigned integers and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_u32_init_fill(rd_matrix_u32* m, const size_t nrows, const size_t ncols, const uint32_t fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_u32_copy(rd_matrix_u32* dest, const rd_matrix_u32* src);

/**
 * @brief Frees the memory of a matrix of 32-bit unsigned integers.
 * @param m       The matrix to free
 */
void rd_matrix_u32_free(rd_matrix_u32* m);

/**
 * @brief Initializes a matrix of 64-bit unsigned integers.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_u64_init(rd_matrix_u64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializesa matrix of 64-bit unsigned integers with zeroes.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 */
void rd_matrix_u64_init_zeroes(rd_matrix_u64* m, const size_t nrows, const size_t ncols);

/**
 * @brief Initializes a matrix of 64-bit unsigned integers and fill it.
 * @param m       Matrix to initialize
 * @param nrows   Number of rows
 * @param ncols   Number of columns
 * @param fill    Value to fill the matrix with
 */
void rd_matrix_u64_init_fill(rd_matrix_u64* m, const size_t nrows, const size_t ncols, const uint64_t fill);

/**
 * @brief Performs a deep copy of 'src' to 'dest'.
 * @param dest   The destination (where to copy)
 * @param src    The matrix to copy
 */
void rd_matrix_u64_copy(rd_matrix_u64* dest, const rd_matrix_u64* src);

/**
 * @brief Frees the memory of a matrix of 64-bit unsigned integers.
 * @param m       The matrix to free
 */
void rd_matrix_u64_free(rd_matrix_u64* m);

#ifdef __cplusplus
}
#endif

#endif
