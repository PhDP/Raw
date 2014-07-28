#ifndef RD_HASH_H_
#define RD_HASH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief The murmur3 32-bit hash.
 *
 * ...
 */
uint32_t rd_murmur3_32(const char *key, uint32_t len, uint32_t seed);

#ifdef __cplusplus
}
#endif

#endif
