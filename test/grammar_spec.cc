#include "catch.hpp"
#include "randamu/grammar.h"

static void view(rd_grammar* g) {
  printf("\n");
  rd_grammar_show(g, stdout);
  printf("\n");
  rd_grammar_show_details(g, stdout);
  printf("\n");
}

TEST_CASE("Create and free simple grammar", "grammar") {
  const char* str = "  <bird-sex-chromosomes>   ::= zz | zw";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);
  REQUIRE(1 == g.nmemb);
  REQUIRE(2 == g.rules[0].nmemb);
  REQUIRE(1 == g.rules[0].alts[0].nmemb);
  REQUIRE(1 == g.rules[0].alts[1].nmemb);
  REQUIRE(-1 == rd_grammar_rule_idx(&g, "<expr>"));
  REQUIRE(0 == rd_grammar_rule_idx(&g, "<bird-sex-chromosomes>"));
  rd_grammar_free(&g);
}

TEST_CASE("Grammar with nonterminals", "grammar") {
  const char* str = "<expr>   ::= monty<python> | <ac><dc> | <fire>  and  <ice>";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);
  REQUIRE(1 == g.nmemb);
  REQUIRE(3 == g.rules[0].nmemb);
  REQUIRE(2 == g.rules[0].alts[0].nmemb);
  REQUIRE(2 == g.rules[0].alts[1].nmemb);
  REQUIRE(5 == g.rules[0].alts[2].nmemb);
  REQUIRE(0 == rd_grammar_rule_idx(&g, "<expr>"));
  REQUIRE(-1 == rd_grammar_rule_idx(&g, "<python>"));
  rd_grammar_free(&g);
}

TEST_CASE("Grammar with multiple production rules", "grammar") {
  // <expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>
  // <op>   ::= * | + | - | /
  // <fun1> ::= sin | cos | exp
  // <var>  ::= x | y
  // <num>  ::= 0 | 1 | 2 | 3 | 4
  const char* str = "<expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>\n<op>   ::= * | + | - | /\n<fun1> ::= sin | cos | exp\n<var>  ::= x | y\n<num>  ::= 0 | 1 | 2 | 3 | 4";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);
  REQUIRE(5 == g.nmemb);
  REQUIRE(5 == g.rules[0].nmemb);
  REQUIRE(5 == g.rules[0].alts[0].nmemb);
  REQUIRE(5 == g.rules[0].alts[1].nmemb);
  REQUIRE(4 == g.rules[0].alts[2].nmemb);
  REQUIRE(1 == g.rules[0].alts[3].nmemb);
  REQUIRE(1 == g.rules[0].alts[4].nmemb);
  REQUIRE(4 == g.rules[1].nmemb);
  REQUIRE(3 == g.rules[2].nmemb);
  REQUIRE(2 == g.rules[3].nmemb);
  REQUIRE(5 == g.rules[4].nmemb);
  REQUIRE(0 == rd_grammar_rule_idx(&g, "<expr>"));
  REQUIRE(1 == rd_grammar_rule_idx(&g, "<op>"));
  REQUIRE(2 == rd_grammar_rule_idx(&g, "<fun1>"));
  REQUIRE(3 == rd_grammar_rule_idx(&g, "<var>"));
  REQUIRE(4 == rd_grammar_rule_idx(&g, "<num>"));
  REQUIRE(-1 == rd_grammar_rule_idx(&g, "<num->"));
  rd_grammar_free(&g);
}

TEST_CASE("Grammar with spaces between alternatives", "grammar") {
  const char* str = "<expr> ::= <expr> <op> <expr>\n     | (<expr><op><expr>) |  \n    <fun1>(<expr>) | <var> | <num>\n<op>   ::= \n* |\n + \n| - \n| /\n<fun1> ::= sin | cos | exp\n<var>  ::= x | y\n<num>  ::= 0 | 1 | 2 | 3 | 4";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);
  REQUIRE(5 == g.nmemb);
  REQUIRE(5 == g.rules[0].nmemb);
  REQUIRE(5 == g.rules[0].alts[0].nmemb);
  REQUIRE(5 == g.rules[0].alts[1].nmemb);
  REQUIRE(4 == g.rules[0].alts[2].nmemb);
  REQUIRE(1 == g.rules[0].alts[3].nmemb);
  REQUIRE(1 == g.rules[0].alts[4].nmemb);
  REQUIRE(4 == g.rules[1].nmemb);
  REQUIRE(3 == g.rules[2].nmemb);
  REQUIRE(2 == g.rules[3].nmemb);
  REQUIRE(5 == g.rules[4].nmemb);
  REQUIRE(0 == rd_grammar_rule_idx(&g, "<expr>"));
  REQUIRE(1 == rd_grammar_rule_idx(&g, "<op>"));
  REQUIRE(2 == rd_grammar_rule_idx(&g, "<fun1>"));
  REQUIRE(3 == rd_grammar_rule_idx(&g, "<var>"));
  REQUIRE(4 == rd_grammar_rule_idx(&g, "<num>"));
  REQUIRE(-1 == rd_grammar_rule_idx(&g, "<num->"));
  rd_grammar_free(&g);
}
