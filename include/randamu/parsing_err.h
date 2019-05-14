/**
 * @file parsing_err.h
 * @brief
 */
#ifndef RANDAMU_PARSING_ERR_H_
#define RANDAMU_PARSING_ERR_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Stores information on potential parsing errors.
 */
typedef struct {
  char* msg;
  size_t idx;
} rd_parsing_err;

/**
 * @brief Initializes a parsing error.
 */
void rd_parsing_err_init(rd_parsing_err* err);

/**
 * @brief Frees the memory of a parsing error.
 */
void rd_parsing_err_free(rd_parsing_err* err);

#ifdef __cplusplus
}
#endif

#endif
