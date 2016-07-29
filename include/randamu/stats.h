/*! \file
 *
 * \brief Basic stats functions.
 */

#ifndef RD_STATS_H_
#define RD_STATS_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Some algorithms work better on sorted data. This function creates a
 * copy of the array, sort it, call the stat function on the sorted data,
 * and return the result after the sorted array is freed.
 *
 * \param base      Base of the array.
 * \param nmemb     Number of elements in the array.
 * \param st        Stat function to call on the sorted data.
 * \return          Results from the stat function.
 */
double rd_sort_stat(const double *base, size_t nmemb, double (*st)(const double *, const void *));

#ifdef __cplusplus
}
#endif

#endif

