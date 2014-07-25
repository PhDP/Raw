#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "compar.h"

int cmp_string_asc(const void *x, const void *y) {
  return strcmp(*(char **)x, *(char **)y);
}

int cmp_string_des(const void *x, const void *y) {
  return strcmp(*(char **)x, *(char **)y);
}

int cmp_char_asc(const void *x, const void *y) {
  return *(char *)x - *(char *)y;
}

int cmp_char_des(const void *x, const void *y) {
  return *(char *)y - *(char *)x;
}

int cmp_uchar_asc(const void *x, const void *y) {
  return *(unsigned char *)x - *(unsigned char *)y;
}

int cmp_uchar_des(const void *x, const void *y) {
  return *(unsigned char *)y - *(unsigned char *)x;
}

int cmp_double_asc(const void *x, const void *y) {
  if (*(double *)x < *(double *)y) {
    return -1;
  } else if (*(double *)x > *(double *)y) {
    return 1;
  }
  return 0;
}

int cmp_double_des(const void *x, const void *y) {
  if (*(double *)x > *(double *)y) {
    return -1;
  } else if (*(double *)x < *(double *)y) {
    return 1;
  }
  return 0;
}

int cmp_float_asc(const void *x, const void *y) {
  if (*(float *)x < *(float *)y) {
    return -1;
  } else if (*(float *)x > *(float *)y) {
    return 1;
  }
  return 0;
}

int cmp_float_des(const void *x, const void *y) {
  if (*(float *)x > *(float *)y) {
    return -1;
  } else if (*(float *)x < *(float *)y) {
    return 1;
  }
  return 0;
}

int cmp_int_asc(const void *x, const void *y) {
  return *(int *)x - *(int *)y;
}

int cmp_int_des(const void *x, const void *y) {
  return *(int *)y - *(int *)x;
}

int cmp_uint_asc(const void *x, const void *y) {
  return *(unsigned int *)x - *(unsigned int *)y;
}

int cmp_uint_des(const void *x, const void *y) {
  return *(unsigned int *)y - *(unsigned int *)x;
}

int cmp_long_asc(const void *x, const void *y) {
  return *(long *)x - *(long *)y;
}

int cmp_long_des(const void *x, const void *y) {
  return *(long *)y - *(long *)x;
}

int cmp_ulong_asc(const void *x, const void *y) {
  return *(unsigned long *)x - *(unsigned long *)y;
}

int cmp_ulong_des(const void *x, const void *y) {
  return *(unsigned long *)y - *(unsigned long *)x;
}
