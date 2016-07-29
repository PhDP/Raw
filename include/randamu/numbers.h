/*! \file
 *
 * \brief Funtions to handle floating point numbers and common numerical
 * problems with them.
 **************************************************************************/

#ifndef RD_NUMBERS_H_
#define RD_NUMBERS_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Round the number according to the default IEEE754 standard. It will
 * round numbers with a 0.5 fraction toward the nearest even number.
 *
 * \param n         Number to round.
 * \return          Rounded number.
 */
int rd_round(double n);

/**
 * \brief Like rd_round but toward odd numbers. This is mostly useful when you
 * need to never round to 0.
 *
 * \param n         Number to round.
 * \return          Rounded number.
 */
int rd_round_odd(double n);

/**
 * \brief Sort an array before summing its values to avoid numerical
 * problems. This will not change the array, a copy is made, sorted,
 * and freed after the sum is computed.
 *
 * \param base      Base of the array of double to sum.
 * \param nmemb     Number of elements in the array.
 * \return          Sum of all the values in the array.
 */
double rd_sortsum(const double *base, int nmemb);

#ifdef __cplusplus
}
#endif

#endif
