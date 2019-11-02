#include "raw/parsing_err.h"

void r_parsing_err_init(r_parsing_err* e) {
  e->msg = NULL;
  e->idx = 0;
}

void r_parsing_err_free(r_parsing_err* e) {
  if (e && e->msg) {
    free(e->msg);
    e->idx = 0;
  }
}
