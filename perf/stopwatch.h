#ifndef RD_STOPWATCH_H_
#define RD_STOPWATCH_H_

#include <stdint.h>

typedef struct {
  uint64_t start;
} rd_stopwatch;

void rd_sw_init(rd_stopwatch *sw);
uint64_t rd_sw_term(const rd_stopwatch *sw);

#endif

