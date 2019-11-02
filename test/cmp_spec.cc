#include "catch.hpp"
#include "raw/cmp.h"

TEST_CASE("Ascending order string comparison function", "cmp") {
  const size_t n = 5;
  char const* strs[] = {"Monoid", "Quasigroup", "Group", "Abelian", "Magma"};
  qsort((void*)strs, n, sizeof(char*), r_cmp_str_asc);
  REQUIRE(0 == strcmp(strs[0], "Abelian"));
  REQUIRE(0 == strcmp(strs[1], "Group"));
  REQUIRE(0 == strcmp(strs[2], "Magma"));
  REQUIRE(0 == strcmp(strs[3], "Monoid"));
  REQUIRE(0 == strcmp(strs[4], "Quasigroup"));
}

TEST_CASE("Descending order string comparison function", "cmp") {
  const size_t n = 9;
  char** strs = (char**)malloc(n * sizeof(char*));
  size_t i = 0;
  for (; i < n; ++i) {
    strs[i] = (char*)malloc(50);
  }

  sprintf(strs[0], "Magnus Carlsen");
  sprintf(strs[1], "Garry Kasparov");
  sprintf(strs[2], "Fabiano Caruana");
  sprintf(strs[3], "Levon Aronian");
  sprintf(strs[4], "Wesley So");
  sprintf(strs[5], "Shakhriyar Mamedyarov");
  sprintf(strs[6], "Maxime Vachier-Lagrave");
  sprintf(strs[7], "Viswanathan Anand");
  sprintf(strs[8], "Vladimir Kramnik");

  qsort((void*)strs, n, sizeof(char*), r_cmp_str_des);

  REQUIRE(0 == strcmp("Wesley So", strs[0]));
  REQUIRE(0 == strcmp("Vladimir Kramnik", strs[1]));
  REQUIRE(0 == strcmp("Viswanathan Anand", strs[2]));
  REQUIRE(0 == strcmp("Shakhriyar Mamedyarov", strs[3]));
  REQUIRE(0 == strcmp("Maxime Vachier-Lagrave", strs[4]));
  REQUIRE(0 == strcmp("Magnus Carlsen", strs[5]));
  REQUIRE(0 == strcmp("Levon Aronian", strs[6]));
  REQUIRE(0 == strcmp("Garry Kasparov", strs[7]));
  REQUIRE(0 == strcmp("Fabiano Caruana", strs[8]));

  for (i = 0; i < n; ++i) {
    free(strs[i]);
  }
  free(strs);
}

TEST_CASE("Ascending order integer comparison function", "cmp") {
  const size_t n = 8;
  size_t xs[] = {8198211, 6, 2984, 8128, 0, 62433, 6, 0};
  qsort((void*)xs, n, sizeof(size_t), r_cmp_sz_asc);
  REQUIRE(0 == xs[0]);
  REQUIRE(0 == xs[1]);
  REQUIRE(6 == xs[2]);
  REQUIRE(6 == xs[3]);
  REQUIRE(2984 == xs[4]);
  REQUIRE(8128 == xs[5]);
  REQUIRE(62433 == xs[6]);
  REQUIRE(8198211 == xs[7]);
}

TEST_CASE("Descending order integer comparison function", "cmp") {
  const size_t n = 10;
  int8_t xs[] = {2, 100, 48, 42, 42, 47, 42, 1, -16, -42};
  qsort((void*)xs, n, sizeof(int8_t), r_cmp_i8_des);
  REQUIRE(100 == xs[0]);
  REQUIRE(48 == xs[1]);
  REQUIRE(47 == xs[2]);
  REQUIRE(42 == xs[3]);
  REQUIRE(42 == xs[4]);
  REQUIRE(42 == xs[5]);
  REQUIRE(2 == xs[6]);
  REQUIRE(1 == xs[7]);
  REQUIRE(-16 == xs[8]);
  REQUIRE(-42 == xs[9]);
}
