#ifndef RD_COMMON_H_
#define RD_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RANDAMU         "0.0.0"
#define RANDAMU_MAJOR   0
#define RANDAMU_MINOR   1
#define RANDAMU_PATCH   0

#include <string.h>

/**
 * \brief A generic swap macro.
 *
 * I'm not always using this code for swapping when I
 * can avoid allocating memory for every swap operation
 * in a tight loop.
 *
 * \param a       Pointer to the first value to swap.
 * \param b       Pointer to the second value to swap.
 * \param size    Size of the data of swap in bytes.
 */
#ifdef _MSC_VER
#define rd_swap(a, b, size) \
  do { \
    uint8_t *tmp = (uint8_t*)malloc(size); \ // alloca???
    memcpy((void*)tmp, (void*)(b), size); \
    memcpy((void*)(b), (void*)(a), size); \
    memcpy((void*)(a), (void*)tmp, size); \
    free(tmp); \
  } while(0)
#else
#define rd_swap(a, b, size) \
  do { \
    uint8_t tmp[size]; \
    memcpy((void*)&tmp, (void*)(b), size); \
    memcpy((void*)(b), (void*)(a), size); \
    memcpy((void*)(a), (void*)&tmp, size); \
  } while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif
