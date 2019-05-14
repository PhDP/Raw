#include "randamu/parsing_err.h"

void rd_parsing_err_init(rd_parsing_err* e) {
  e->msg = NULL;
  e->idx = 0;
}

void rd_parsing_err_free(rd_parsing_err* e) {
  if (e && e->msg) {
    free(e->msg);
    e->idx = 0;
  }
}
