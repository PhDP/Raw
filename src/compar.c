#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "randamu/compar.h"

int cmp_string_asc(const void *x, const void *y) {
  return strcmp(*(char **)x, *(char **)y);
}

int cmp_string_des(const void *x, const void *y) {
  return strcmp(*(char **)x, *(char **)y);
}

int cmp_char_asc(const void *x, const void *y) {
  if (*(char *)x < *(char *)y) {
    return -1;
  } else if (*(char *)x > *(char *)y) {
    return 1;
  }
  return 0;
}

int cmp_char_des(const void *x, const void *y) {
  if (*(char *)x > *(char *)y) {
    return -1;
  } else if (*(char *)x < *(char *)y) {
    return 1;
  }
  return 0;
}

int cmp_uchar_asc(const void *x, const void *y) {
  if (*(unsigned char *)x < *(unsigned char *)y) {
    return -1;
  } else if (*(unsigned char *)x > *(unsigned char *)y) {
    return 1;
  }
  return 0;
}

int cmp_uchar_des(const void *x, const void *y) {
  if (*(unsigned char *)x > *(unsigned char *)y) {
    return -1;
  } else if (*(unsigned char *)x < *(unsigned char *)y) {
    return 1;
  }
  return 0;
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
  if (*(int *)x < *(int *)y) {
    return -1;
  } else if (*(int *)x > *(int *)y) {
    return 1;
  }
  return 0;
}

int cmp_int_des(const void *x, const void *y) {
  if (*(int *)x > *(int *)y) {
    return -1;
  } else if (*(int *)x < *(int *)y) {
    return 1;
  }
  return 0;
}

int cmp_uint_asc(const void *x, const void *y) {
  if (*(unsigned int *)x < *(unsigned int *)y) {
    return -1;
  } else if (*(unsigned int *)x > *(unsigned int *)y) {
    return 1;
  }
  return 0;
}

int cmp_uint_des(const void *x, const void *y) {
  if (*(unsigned int *)x > *(unsigned int *)y) {
    return -1;
  } else if (*(unsigned int *)x < *(unsigned int *)y) {
    return 1;
  }
  return 0;
}

int cmp_long_asc(const void *x, const void *y) {
  if (*(long *)x < *(long *)y) {
    return -1;
  } else if (*(long *)x > *(long *)y) {
    return 1;
  }
  return 0;
}

int cmp_long_des(const void *x, const void *y) {
  if (*(long *)x > *(long *)y) {
    return -1;
  } else if (*(long *)x < *(long *)y) {
    return 1;
  }
  return 0;
}

int cmp_ulong_asc(const void *x, const void *y) {
  if (*(unsigned long *)x < *(unsigned long *)y) {
    return -1;
  } else if (*(unsigned long *)x > *(unsigned long *)y) {
    return 1;
  }
  return 0;
}

int cmp_ulong_des(const void *x, const void *y) {
  if (*(unsigned long *)x > *(unsigned long *)y) {
    return -1;
  } else if (*(unsigned long *)x < *(unsigned long *)y) {
    return 1;
  }
  return 0;
}
