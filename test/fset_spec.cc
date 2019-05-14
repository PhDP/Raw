#include "catch.hpp"
#include "randamu/fset.h"
#include "randamu/cmp.h"

RANDAMU_FLATSET(fset_u32, uint32_t, size_t, rd_cmp_u32_asc)

TEST_CASE("Add, remove, find from a sorted array of uint32_t (ascending order)", "fset") {
  size_t capacity = 0;
  size_t nmemb = 0;
  uint32_t* xs;

  uint32_t x = 42;
  fset_u32_add(&xs, &x, &nmemb, &capacity);
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  REQUIRE(1 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(42 == xs[0]);

  x = 6;
  fset_u32_add(&xs, &x, &nmemb, &capacity);
  x = 2;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  REQUIRE(3 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(2 == xs[0]);
  REQUIRE(6 == xs[1]);
  REQUIRE(42 == xs[2]);

  x = 59;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 67;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 0;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 67;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  REQUIRE(6 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(0 == xs[0]);
  REQUIRE(2 == xs[1]);
  REQUIRE(6 == xs[2]);
  REQUIRE(42 == xs[3]);
  REQUIRE(59 == xs[4]);
  REQUIRE(67 == xs[5]);

  x = 8127;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 17;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 6000;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  x = 8127;
  fset_u32_add(&xs, &x, &nmemb, &capacity);

  REQUIRE(9 == nmemb);
  REQUIRE(12 == capacity);
  REQUIRE(0 == xs[0]);
  REQUIRE(2 == xs[1]);
  REQUIRE(6 == xs[2]);
  REQUIRE(17 == xs[3]);
  REQUIRE(42 == xs[4]);
  REQUIRE(59 == xs[5]);
  REQUIRE(67 == xs[6]);
  REQUIRE(6000 == xs[7]);
  REQUIRE(8127 == xs[8]);

  x = 16;
  fset_u32_del(&xs, &x, &nmemb);

  REQUIRE(9 == nmemb);
  REQUIRE(12 == capacity);
  REQUIRE(0 == xs[0]);
  REQUIRE(8127 == xs[8]);

  x = 42;
  fset_u32_del(&xs, &x, &nmemb);

  x = 0;
  fset_u32_del(&xs, &x, &nmemb);

  x = 67;
  fset_u32_del(&xs, &x, &nmemb);

  x = 8127;
  fset_u32_del(&xs, &x, &nmemb);
  fset_u32_del(&xs, &x, &nmemb);

  REQUIRE(5 == nmemb);
  REQUIRE(12 == capacity);
  REQUIRE(2 == xs[0]);
  REQUIRE(6 == xs[1]);
  REQUIRE(17 == xs[2]);
  REQUIRE(59 == xs[3]);
  REQUIRE(6000 == xs[4]);

  free(xs);
}

RANDAMU_FLATSMAP(fsmap_sz_sz, size_t, size_t, rd_cmp_sz_des)

TEST_CASE("Insert size_t -> size_t flatmap (sorted in descending order)", "fsmap") {
  size_t capacity = 0;
  size_t nmemb = 0;
  size_t* pairs;

  size_t key = 6;
  size_t val = 0;
  fsmap_sz_sz_add(&pairs, &key, &val, &nmemb, &capacity);
  fsmap_sz_sz_add(&pairs, &key, &val, &nmemb, &capacity);

  REQUIRE(1 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(6 == pairs[0]);
  REQUIRE(0 == pairs[1]);

  key = 1;
  val = 100;
  fsmap_sz_sz_add(&pairs, &key, &val, &nmemb, &capacity);

  REQUIRE(2 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(6 == pairs[0]);
  REQUIRE(0 == pairs[1]);
  REQUIRE(1 == pairs[2]);
  REQUIRE(100 == pairs[3]);

  key = 6;
  val = 12;
  fsmap_sz_sz_add(&pairs, &key, &val, &nmemb, &capacity);

  REQUIRE(2 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(6 == pairs[0]);
  REQUIRE(12 == pairs[1]);
  REQUIRE(1 == pairs[2]);
  REQUIRE(100 == pairs[3]);

  free(pairs);
}

typedef struct {
  char* title;
  int32_t wordcount;
} shakespeare_play;

RANDAMU_FLATMAP(fmap_str_i32, shakespeare_play, char*, title, int32_t, wordcount, size_t, rd_cmp_str_asc)

TEST_CASE("Insert str -> int32_t flatmap (sorted in ascending order)", "fsmap") {
  size_t capacity = 0;
  size_t nmemb = 0;
  shakespeare_play* plays;
  shakespeare_play p;

  p.title = (char*)malloc(50);
  sprintf(p.title, "Tempest");
  p.wordcount = 16630;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  REQUIRE(1 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(0 == strcmp("Tempest", plays[0].title));
  REQUIRE(16633 == plays[0].wordcount);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Hamlet");
  p.wordcount = 30557;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Othello");
  p.wordcount = 26450;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  REQUIRE(3 == nmemb);
  REQUIRE(8 == capacity);
  REQUIRE(0 == strcmp("Hamlet", plays[0].title));
  REQUIRE(30557 == plays[0].wordcount);
  REQUIRE(0 == strcmp("Othello", plays[1].title));
  REQUIRE(26450 == plays[1].wordcount);
  REQUIRE(0 == strcmp("Tempest", plays[2].title));
  REQUIRE(16633 == plays[2].wordcount);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Timon of Athens");
  p.wordcount = 18216;
  REQUIRE(fmap_str_i32_add(&plays, &p, &nmemb, &capacity));

  p.title = (char*)malloc(50);
  sprintf(p.title, "As You Like It");
  p.wordcount = 21690;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Hamlet");
  p.wordcount = 30557;
  REQUIRE(!fmap_str_i32_add(&plays, &p, &nmemb, &capacity));

  p.title = (char*)malloc(50);
  sprintf(p.title, "Antony and Cleopatra");
  p.wordcount = 24905;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "King Lear");
  p.wordcount = 26145;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Merry Wives of Windsor");
  p.wordcount = 21845;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Romeo and Juliet");
  p.wordcount = 24545;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  p.title = (char*)malloc(50);
  sprintf(p.title, "Cymbeline");
  p.wordcount = 27565;
  fmap_str_i32_add(&plays, &p, &nmemb, &capacity);

  // Cleanup:
  size_t i = 0;
  for (; i < nmemb; ++i) {
    free(plays[i].title);
  }
  free(plays);
}

