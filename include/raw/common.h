/**
 * @file common.h
 * @brief Common includes and macros for raw.
 */
#ifndef RAW_COMMON_H_
#define RAW_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "SFMT/SFMT.h"

#ifdef RAW_CUDA
//  #include <cuda/...>
#endif

/**
 * @brief Checks if 'n' is a power of two.
 */
#define r_is_power_of_two(n)    (((n) != 0) && (((n) & (~(n) + 1)) == (n)))

#ifndef RAW_INITIAL_GRAPH_CAPACITY
#define RAW_INITIAL_GRAPH_CAPACITY 8
#endif

#endif
