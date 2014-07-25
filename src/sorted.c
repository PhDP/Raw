#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bogosort.h"

bool sorted(void *base, size_t nmemb, size_t size,
            int (*cmp)(const void *, const void *)) {
  if (size == 0) {
    return true;
  }
  register unsigned char *a = (base), *b = (base) + size,
                         *end = (base) + (size * nmemb);
  while (b != end) {
    if (cmp(a, b) > 0) {
      return false;
    }
    a = b, b += size;
  }
  return true;
}
