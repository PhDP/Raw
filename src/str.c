#include "raw/str.h"

size_t r_strcat(char** dest, size_t* dest_length, size_t* dest_capacity, const char* source) {
  const size_t source_length = strlen(source);
  if (source_length == 0) {
    return *dest_length;
  }
  if (*dest_length + source_length + 1 >= *dest_capacity) {
    *dest_capacity = *dest_length + source_length + 1;
    *dest = (char*)realloc(*dest, *dest_capacity);
  }
  // In case dest is null and has just been allocated with realloc, ensure it is null-terminated:
  if (*dest_length == 0) {
    *dest[0] = '\0';
  }
  *dest_length += source_length;
  *dest = strcat(*dest, source);
  return *dest_length;
}

int r_surrounded(const char* txt, const char left, const char right) {
  if (txt[0] != left) {
    return 0;
  }
  size_t idx = 1;
  while (txt[idx] != '\0') {
    ++idx;
  }
  return txt[idx - 1] == right;
}

char* r_read_file(const char* filename) {
  FILE* f = fopen(filename, "rb");
  if (f) {
    fseek(f, 0, SEEK_END);
    const long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buffer = (char*)malloc(length);
    if (buffer) {
      const size_t n = fread(buffer, 1, length, f);
    }
    fclose(f);
    return buffer;
  }
  return NULL;
}
