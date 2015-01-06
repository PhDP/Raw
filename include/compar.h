/*! \file
 *
 * \brief The functions compare int, double, int, long, etc. They take two
 * variables and return a number below 0 if the first should be placed
 * before the second, 0 if they are equal, and a number greater than 0
 * if the first should be placed after the second. For all types there are two
 * functions, one finishing with 'asc' and the other with 'des'. 'asc' stands
 * for 'ascending order' and 'des' for 'descending order'.
 **************************************************************************/

#ifndef RD_COMPAR_H_
#define RD_COMPAR_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Used to sort the strings in ascending order.
 *
 * \param x         First string.
 * \param y         Second string.
 * \return          A negative number if x should be before y, 0 if equal, a
 *positive number otherwise.
 */
int cmp_string_asc(const void *x, const void *y);

/**
 * \brief Used to sort the strings in descending order.
 *
 * \param x         First string.
 * \param y         Second string.
 * \return          A positive number if x should be before y, 0 if equal, a
 *negative number otherwise.
 */
int cmp_string_des(const void *x, const void *y);

/**
 * \brief Used to sort characters in ascending order.
 *
 * \param x         First char.
 * \param y         Second char.
 * \return          A negative number if x should be before y, 0 if equal, a
 *positive number otherwise.
 */
int cmp_char_asc(const void *x, const void *y);

/**
 * \brief Used to sort characters in descending order.
 *
 * \param x         First char.
 * \param y         Second char.
 * \return          A positive number if x should be before y, 0 if equal, a
 *negative number otherwise.
 */
int cmp_char_des(const void *x, const void *y);

/**
 * \brief Used to sort unsigned characters in ascending order.
 *
 * \param x         First unsigned char.
 * \param y         Second unsigned char.
 * \return          A negative number if x should be before y, 0 if equal, a
 *positive number otherwise.
 */
int cmp_uchar_asc(const void *x, const void *y);

/**
 * \brief Used to sort unsigned characters in descending order.
 *
 * \param x         First unsigned char.
 * \param y         Second unsigned char.
 * \return          A positive number if x should be before y, 0 if equal, a
 *negative number otherwise.
 */
int cmp_uchar_des(const void *x, const void *y);

/**
 * \brief Used to sort doubles in ascending order.
 *
 * \param x         First double.
 * \param y         Second double.
 * \return          -1 if x < y, 0 if x == y, 1 if x > y.
 */
int cmp_double_asc(const void *x, const void *y);

/**
 * \brief Used to sort doubles in ascending order.
 *
 * \param x         First double.
 * \param y         Second double.
 * \return          1 if x < y, 0 if x == y, -1 if x > y.
 */
int cmp_double_des(const void *x, const void *y);

/**
 * \brief Used to sort floats in ascending order.
 *
 * \param x         First float.
 * \param y         Second float.
 * \return          -1 if x < y, 0 if x == y, 1 if x > y.
 */
int cmp_float_asc(const void *x, const void *y);

/**
 * \brief Used to sort floats in ascending order.
 *
 * \param x         First float.
 * \param y         Second float.
 * \return          1 if x < y, 0 if x == y, -1 if x > y.
 */
int cmp_float_des(const void *x, const void *y);

/**
 * \brief Used to sort integers in ascending order.
 *
 * \param x         First int.
 * \param y         Second int.
 * \return          x - y.
 */
int cmp_int_asc(const void *x, const void *y);

/**
 * \brief Used to sort integers in descending order.
 *
 * \param x         First int.
 * \param y         Second int.
 * \return          y - x.
 */
int cmp_int_des(const void *x, const void *y);

/**
 * \brief Used to sort unsigned integers in ascending order.
 *
 * \param x         First unsigned int.
 * \param y         Second unsigned int.
 * \return          x - y.
 */
int cmp_uint_asc(const void *x, const void *y);

/**
 * \brief Used to sort unsigned integers in descending order.
 *
 * \param x         First unsigned int.
 * \param y         Second unsigned int.
 * \return          y - x.
 */
int cmp_uint_des(const void *x, const void *y);

/**
 * \brief Used to sort longs in ascending order.
 *
 * \param x         First long.
 * \param y         Second long.
 * \return          x - y.
 */
int cmp_long_asc(const void *x, const void *y);

/**
 * \brief Used to sort longs in descending order.
 *
 * \param x         First long.
 * \param y         Second long.
 * \return          y - x.
 */
int cmp_long_des(const void *x, const void *y);

/**
 * \brief Used to sort unsigned longs in ascending order.
 *
 * \param x         First unsigned long.
 * \param y         Second unsigned long.
 * \return          x - y.
 */
int cmp_ulong_asc(const void *x, const void *y);

/**
 * \brief Used to sort unsigned longs in descending order.
 *
 * \param x         First unsigned long.
 * \param y         Second unsigned long.
 * \return          y - x.
 */
int cmp_ulong_des(const void *x, const void *y);

#ifdef __cplusplus
}
#endif

#endif
