/**
 * @file fset.h
 * @brief Macros used to generate functions to insert/remove elements in sorted arrays ('flatsets').
 *
 * These macros are mostly used internally to support fast sets and maps with few elements (a few
 * hundreds). They are used for the adjacency list in graphs and the list of variables in factors,
 * among other things. They come in three flavors: FLATSET macros generate functions for sets,
 * FLATSMAP generates functions for (key, value) pairs where the key and value have the same type,
 * and FLATMAP generates functions for (kay, value) pairs where the key and the value are of
 * different type.
 *
 * The 'add' function will return 1 only if a new element is inserted. In the case of maps,
 * if the key is present, it'll do nothing. To simplify memory management, an explicit call to update
 * must be made to update values.
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DO NOT ALLOW UPDATES!!!!!!!
 *
 * For consistency, all the generated functions take a reference to the array of elements (KEY**)
 * along with references to the key to add/delete/find, number of elements and capacity. This
 * way, the function to insert and remove can modify the number of members, capacity, and even
 * reallocate memory to the array when necessary.
 *
 * RANDAMU_FLATSET generates PREFIX_add, PREFIX_del, and PREFIX_find to add, delete, and
 * find unique keys into a sorted array.
 *
 * RANDAMU_FLATSMAP generates PREFIX_add, PREFIX_del, and PREFIX_find to add, delete, and
 * find unique keys, plus a function PREFIX_value to get the value associated with a given key.
 *
 * RANDAMU_FLATMAP
 */
#ifndef RANDAMU_FSET_H_
#define RANDAMU_FSET_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates functions to add, remove, and find keys in a sorted array.
 *
 * This function will reallocate memory and increment capacity by 1.5 * capacity if the
 * key doesn't fit in the array.
 *
 * @param NAME_PREFIX     Prefix for each function name.
 * @param KEY_TYPE        Type of the keys and the array of keys.
 * @param SIZE            Type for the sizes (capacity and nmemb), typically size_t.
 * @param CMP             Comparison function (see cmp.h).
 */
#define RANDAMU_FLATSET(NAME_PREFIX, KEY_TYPE, SIZE, CMP) \
  static int NAME_PREFIX ## _add(KEY_TYPE** keys, const KEY_TYPE* k, SIZE* nmemb, SIZE* capacity) { \
    if (*nmemb == 0) { \
      if (*capacity == 0) { \
        *capacity = 8; \
        *keys = (KEY_TYPE*)malloc(8 * sizeof(KEY_TYPE)); \
      } \
      (*keys)[0] = *k; \
      (*nmemb)++; \
      return 1; \
    } \
    SIZE a = 0, b = *nmemb, idx; \
    KEY_TYPE* p; \
    while (a < b) { \
      idx = (a + b) / 2; \
      p = (*keys + idx); \
      const int comparison = CMP((const void*)k, (const void*)p); \
      if (comparison < 0) { \
        b = idx; \
      } else if (comparison > 0) { \
        a = idx + 1; \
      } else { \
        return 0; \
      } \
    } \
    if (*capacity == *nmemb) { \
      *capacity = *capacity < 6? 8 : (3 * *capacity) >> 1; \
      *keys = (KEY_TYPE*)realloc(*keys, *capacity * sizeof(KEY_TYPE)); \
    } \
    if (a < *nmemb) { \
      const size_t size = (*nmemb - a) * sizeof(KEY_TYPE); \
      memmove((void*)(*keys + a + 1), (const void*)(*keys + a), size); \
    } \
    (*keys)[a] = *k; \
    (*nmemb)++; \
    return 1; \
  } \
  \
  static int NAME_PREFIX ## _del(KEY_TYPE** keys, const KEY_TYPE* k, SIZE* nmemb) { \
    if (*nmemb == 0) { \
      return 0; \
    } \
    SIZE a = 0, b = *nmemb, idx; \
    KEY_TYPE* p; \
    while (a < b) { \
      idx = (a + b) / 2; \
      p = (*keys + idx); \
      const int comparison = CMP((const void*)k, (const void*)p); \
      if (comparison < 0) { \
        b = idx; \
      } else if (comparison > 0) { \
        a = idx + 1; \
      } else { \
        (*nmemb)--; \
        /* Unless the key to remove is the last, move memory: */ \
        if (idx != *nmemb) { \
          memmove((void*)p, (void*)(p + 1), (*nmemb - idx) * sizeof(KEY_TYPE)); \
        } \
        return 1; \
      } \
    } \
    return 0; \
  } \
  \
  static KEY_TYPE* NAME_PREFIX ## _find(const KEY_TYPE** keys, const KEY_TYPE* k, const SIZE* nmemb) { \
    return (KEY_TYPE*)bsearch((const void*)k, (const void*)(*keys), *nmemb, sizeof(KEY_TYPE), CMP); \
  }

/**
 * @brief ...
 * @param NAME_PREFIX     Prefix for each function name.
 * @param KEY_TYPE        Type for both the key and the value.
 * @param SIZE            Type for the sizes (capacity and nmemb), typically size_t.
 * @param CMP             Comparison function (see cmp.h).
 *
 * Capacity and nmemb are in pairs.
 */
#define RANDAMU_FLATSMAP(NAME_PREFIX, KEY_TYPE, SIZE, CMP) \
  static int NAME_PREFIX ## _add (KEY_TYPE** pairs, const KEY_TYPE* k, const KEY_TYPE* v, SIZE* nmemb, SIZE* capacity) { \
    if (*nmemb == 0) { \
      if (*capacity == 0) { \
        *capacity = 8; \
        *pairs = (KEY_TYPE*)malloc(16 * sizeof(KEY_TYPE)); \
      } \
      (*pairs)[0] = *k; \
      (*pairs)[1] = *v; \
      (*nmemb)++; \
      return 1; \
    } \
    SIZE a = 0, b = *nmemb * 2, idx; \
    KEY_TYPE* p; \
    while (a < b) { \
      idx = (a + b) / 2; \
      p = (*pairs + idx); \
      const int comparison = CMP((const void*)k, (const void*)p); \
      if (comparison < 0) { \
        b = idx; \
      } else if (comparison > 0) { \
        a = idx + 2; \
      } else { \
        /* Updates are not allowed: (*pairs)[a + 1] = *v; */ \
        return 0; \
      } \
    } \
    if (*capacity == *nmemb) { \
      *capacity = *capacity < 6? 8 : (3 * *capacity) >> 1; \
      *pairs = (KEY_TYPE*)realloc(*pairs, 2 * *capacity * sizeof(KEY_TYPE)); \
    } \
    if (a < *nmemb) { \
      const size_t size = 2 * (*nmemb - a) * sizeof(KEY_TYPE); \
      memmove((void*)(*pairs + a + 2), (const void*)(*pairs + a), size); \
    } \
    (*pairs)[a] = *k; \
    (*pairs)[a + 1] = *v; \
    (*nmemb)++; \
    return 1; \
  } \
  \
  static int NAME_PREFIX ## _del(KEY_TYPE** pairs, const KEY_TYPE* k, SIZE* nmemb) { \
    if (*nmemb == 0) { \
      return 0; \
    } \
    SIZE a = 0, b = 2 * *nmemb, idx; \
    KEY_TYPE* p; \
    while (a < b) { \
      idx = (a + b) / 2; \
      p = (*pairs + idx); \
      const int comparison = CMP((const void*)k, (const void*)p); \
      if (comparison < 0) { \
        b = idx; \
      } else if (comparison > 0) { \
        a = idx + 1; \
      } else { \
        (*nmemb)--; \
        /* Unless the key to remove is the last, move memory: */ \
        if (idx != *nmemb) { \
          memmove((void*)p, (void*)(p + 2), 2 * (*nmemb - idx) * sizeof(KEY_TYPE)); \
        } \
        return 1; \
      } \
    } \
    return 0; \
  } \
  \
  static KEY_TYPE* NAME_PREFIX ## _find (const KEY_TYPE** keys, const KEY_TYPE* k, const SIZE* nmemb) { \
    return (KEY_TYPE*)bsearch((const void*)k, (const void*)(*keys), *nmemb, sizeof(KEY_TYPE), CMP); \
  } \
  \
  static KEY_TYPE* NAME_PREFIX ## _value (const KEY_TYPE** keys, const KEY_TYPE* k, const SIZE* nmemb) { \
    KEY_TYPE* r = (KEY_TYPE*)bsearch((const void*)k, (const void*)(*keys), *nmemb, sizeof(KEY_TYPE), CMP); \
    return r? r + 1 : NULL; \
  }

/**
 * @brief Generates functions for flat maps.
 *
 * @param FUNCTION_NAME   Name of the generated static function.
 * @param KEY             Type for the key.
 * @param VALUE           Type for the pair.
 * @param SIZE            Type for the sizes (capacity and nmemb), typically size_t.
 * @param CMP             Comparison function (see cmp.h).
 *
 * Capacity and nmemb are in pairs.
 */
#define RANDAMU_FLATMAP(NAME_PREFIX, PAIR_TYPE, KEY_TYPE, KEY_NAME, VALUE_TYPE, VALUE_NAME, SIZE, CMP) \
  static int NAME_PREFIX ## _add(PAIR_TYPE** kvs, const PAIR_TYPE* kv, SIZE* nmemb, SIZE* capacity) { \
    if (*nmemb == 0) { \
      if (*capacity == 0) { \
        *capacity = 8; \
        *kvs = (PAIR_TYPE*)malloc(8 * sizeof(PAIR_TYPE)); \
      } \
      (*kvs)[0] = *kv; \
      (*nmemb)++; \
      return 1; \
    } \
    SIZE a = 0, b = *nmemb, idx; \
    PAIR_TYPE* p; \
    while (a < b) { \
      idx = (a + b) / 2; \
      p = (*kvs + idx); \
      const int comparison = CMP((const void*)(&kv->KEY_NAME), (const void*)(&p->KEY_NAME)); \
      if (comparison < 0) { \
        b = idx; \
      } else if (comparison > 0) { \
        a = idx + 1; \
      } else { \
        ((*kvs)[a + 1]).VALUE_NAME = kv->VALUE_NAME; \
        return 1; \
      } \
    } \
    if (*capacity == *nmemb) { \
      *capacity = *capacity < 6? 8 : (3 * *capacity) >> 1; \
      *kvs = (PAIR_TYPE*)realloc(*kvs, *capacity * sizeof(PAIR_TYPE)); \
    } \
    if (a < *nmemb) { \
      const size_t size = (*nmemb - a) * sizeof(PAIR_TYPE); \
      memmove((void*)(*kvs + a + 1), (const void*)(*kvs + a), size); \
    } \
    (*kvs)[a] = *kv; \
    (*nmemb)++; \
    return 1; \
  }

#ifdef __cplusplus
}
#endif

#endif

