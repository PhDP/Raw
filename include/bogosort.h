#ifndef RD_BOGOSORT_H_
#define RD_BOGOSORT_H_

#include "well.h"

// For C++ compilers:
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
 *are not in the right order.
 * \return          True if the array is sorted, false otherwise.
 */
bool sorted(void *base, size_t nmemb, size_t size,
            int (*cmp)(const void *, const void *));

/**
 * \brief Shuffles an array with Knuth's in-place algorithm.
 *
 * \param base     The array to shuffle.
 * \param nmemb    Number of elements in the array.
 * \param size     Size of the data (in bytes) inside the array.
 * \param rng      An initialized well1024 random number generator.
 */
void knuth_shuffle(void *base, size_t nmemb, size_t size, well *rng);

/**
 * \brief Sort with bogosort!
 *
 * Use the well random number generator and the provided seed.
 *
 * \param base     The array to sort.
 * \param length   Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements (same as the argument for qsort,
 *see compar.h).
 * \param seed     A number (greater than 0) to seed the random generator.
 * \return         The number of attempts needed to sort.
 */
size_t bogosort(void *x, size_t nmemb, size_t size,
                int (*cmp)(const void *, const void *), unsigned int seed);

/**
 * \brief Sort with bogosort!
 *
 * Use the well random number generator and is seeded with time.
 *
 * \param base     The array to sort.
 * \param length   Number of elements in the array.
 * \param size     Size of an element.
 * \param cmp      Function to compare elements (same as the argument for qsort,
 *see compar.h).
 * \return         The number of attempts needed to sort.
 */
size_t bogosort_noseed(void *x, size_t nmemb, size_t size,
                       int (*cmp)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif

