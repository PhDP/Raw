/*! \file
 *
 * \brief Sort algorithms, including the infamous bogosort and, well
 * more useful algorithms.
 */

#ifndef RD_SORT_H_
#define RD_SORT_H_

#include "randamu/common.h"
#include "randamu/well1024.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Checks if the array is sorted.
 *
 * \param base      Base of the array.
 * \param nmemb     Number of elements in the array.
 * \param size      Size, in bytes, of each element.
 * \param cmp       Function that returns a number above 0 if it's two arguments
 *                  are not in the right order.
 * \return          True if the array is sorted, false otherwise.
 */
bool rd_sorted(const void *base, size_t nmemb, size_t size,
            int (*cmp)(const void *, const void *));

/**
 * \brief Shuffles an array with Knuth's in-place algorithm.
 *
 * \param base     The array to shuffle.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of the data (in bytes) inside the array.
 * \param rng      An initialized well1024 random number generator.
 */
void rd_knuth_shuffle(void *base, size_t nmemb, size_t size, rd_well1024 *r);

/**
 * \brief Sort with bogosort!
 *
 * \param base     The array to sort.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements (same as the argument for qsort,
 *                 see compar.h).
 * \param r        A random number generator.
 * \return         The number of attempts needed to sort.
 */
size_t rd_bogosort(void *x, size_t nmemb, size_t size,
                   int (*cmp)(const void *, const void *), rd_well1024 *r);

/**
 * \brief Bogosort algorithm with the same type signature as qsort, so it
 * can replace it.
 *
 * \param base     The array to sort.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements (same as the argument for qsort,
 *                 see compar.h).
 */
void rd_stdbogosort(void *x, size_t nmemb, size_t size,
                    int (*cmp)(const void *, const void *));

/**
 * \brief Insertion sort.
 *
 * \param base     The array to sort.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements.
 */
void rd_isort(void *x, size_t nmemb, size_t size,
              int (*cmp)(const void *, const void *));

/**
 * \brief Partial sort algorithm.
 *
 * \param base     The array to sort.
 * \param nmemb    Number of elements in the array.
 * \param tosort   Number of elements to sort.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements.
 */
void rd_psort(void *x, size_t nmemb, size_t tosort, size_t size,
              int (*cmp)(const void *, const void *));

/**
 * \brief Pick the first, last, and median elements of an array, sort
 * them, and return the median.
 *
 * For [1, 2, 3, 4, 0], the function will pick 1, 3, 0, sort them into
 * [0, 2, 1, 4, 3], and return 1.
 *
 * \param base     The base of the array.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements.
 * \return         A pointer to the median value in the array.
 */
void * rd_median_of_three(void *base, size_t nmemb, size_t size,
                        int (*cmp)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif

