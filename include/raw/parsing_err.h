/**
 * @file parsing_err.h
 * @brief
 */
#ifndef RAW_PARSING_ERR_H_
#define RAW_PARSING_ERR_H_

#include "raw/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Stores information on potential parsing errors.
 */
typedef struct {
  char* msg;
  size_t idx;
} r_parsing_err;

/**
 * @brief Initializes a parsing error.
 */
void r_parsing_err_init(r_parsing_err* err);

/**
 * @brief Frees the memory of a parsing error.
 */
void r_parsing_err_free(r_parsing_err* err);

#ifdef __cplusplus
}
#endif

#endif
