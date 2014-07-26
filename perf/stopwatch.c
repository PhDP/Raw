// Taken from https://github.com/nanomsg/nanomsg/ (also MIT-licensed).

#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#include "stopwatch.h"

void rd_sw_init(rd_stopwatch *sw) {
  struct timeval tv;
  int rc = gettimeofday(&tv, NULL);
  assert(rc == 0);
  sw->start = (uint64_t)(((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec);
}

uint64_t rd_sw_term(const rd_stopwatch *sw) {
  struct timeval tv;
  uint64_t end;
  int rc = gettimeofday (&tv, NULL);
  assert(rc == 0);
  end = (uint64_t)(((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec);
  return end - sw->start;
}

