/**
 * @file common.h
 * @brief Common includes and macros for Akarui.
 */
#ifndef RANDAMU_COMMON_H_
#define RANDAMU_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "SFMT/SFMT.h"

#ifdef RANDAMU_CUDA
//  #include <cuda/...>
#endif

/**
 * @brief Checks if 'n' is a power of two.
 */
#define rd_is_power_of_two(n)    (((n) != 0) && (((n) & (~(n) + 1)) == (n)))

#ifndef RANDAMU_INITIAL_GRAPH_CAPACITY
#define RANDAMU_INITIAL_GRAPH_CAPACITY 8
#endif

#endif
