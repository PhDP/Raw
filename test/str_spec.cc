#include "catch.hpp"
#include "randamu/str.h"

TEST_CASE("surrounded with empty string", "str") {
  REQUIRE(!rd_surrounded("", '(', ')'));
}

TEST_CASE("surrounded with only the surrounding characters", "str") {
  REQUIRE(rd_surrounded("()", '(', ')'));
}

TEST_CASE("surrounded with xml node", "str") {
  REQUIRE(rd_surrounded("<hello-world>", '<', '>'));
}

TEST_CASE("surrounded with xml node (without the left symbol)", "str") {
  REQUIRE(!rd_surrounded("hello-world>", '<', '>'));
}

TEST_CASE("surrounded with xml node (without the right symbol)", "str") {
  REQUIRE(!rd_surrounded("<hello-world", '<', '>'));
}

TEST_CASE("surrounded with xml node (without any symbols)", "str") {
  REQUIRE(!rd_surrounded("hello-world", '<', '>'));
}

TEST_CASE("string concact with empty strings") {
  size_t capacity = 0;
  size_t length = 0;
  char* str;
  REQUIRE(0 == rd_strcat(&str, &length, &capacity, ""));
}

TEST_CASE("string concact with empty destination") {
  size_t capacity = 0;
  size_t length = 0;
  char* str;
  REQUIRE(66 == rd_strcat(&str, &length, &capacity, "All the world's a stage,\nAnd all the women and men merely players;"));
  REQUIRE(66 == length);
  REQUIRE(67 == capacity);
  REQUIRE(0 == strcmp(str, "All the world's a stage,\nAnd all the women and men merely players;"));
}

TEST_CASE("string concact with empty source") {
  size_t capacity = 11;
  size_t length = 10;
  char* str = (char*)malloc(capacity);
  sprintf(str, "O Freunde!");
  REQUIRE(10 == rd_strcat(&str, &length, &capacity, ""));
  REQUIRE(10 == length);
  REQUIRE(11 == capacity);
  REQUIRE(0 == strcmp(str, "O Freunde!"));
}

TEST_CASE("string concact with non-empty strings") {
  size_t capacity = 8128;
  size_t length = strlen("굴러온");
  const size_t full_length = strlen("굴러온 돌이 박힌 돌 빼낸다");
  char* str = (char*)malloc(capacity);
  sprintf(str, "굴러온");
  REQUIRE(full_length == rd_strcat(&str, &length, &capacity, " 돌이 박힌 돌 빼낸다"));
  REQUIRE(full_length == length);
  REQUIRE(8128 == capacity);
  REQUIRE(0 == strcmp(str, "굴러온 돌이 박힌 돌 빼낸다"));
}
