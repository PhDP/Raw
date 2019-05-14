#include "catch.hpp"
#include "randamu/codons.h"
#include <time.h>

TEST_CASE("Generate simple strings from grammar", "codons") {
  // <expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>
  // <op>   ::= * | + | - | /
  // <fun1> ::= sin | cos | exp
  // <var>  ::= x | y
  // <num>  ::= 0 | 1 | 2 | 3 | 4
  const char* str = "<expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>\n<op>   ::= * | + | - | /\n<fun1> ::= sin | cos | exp\n<var>  ::= x | y\n<num>  ::= 0 | 1 | 2 | 3 | 4";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);

  rd_codons c;
  rd_codons_init(&c, 6);
  c.codons[0] = 7;
  c.codons[1] = 1;
  c.codons[2] = 3;
  c.codons[3] = 5;
  c.codons[4] = 7;
  c.codons[5] = 8;

  char* s = rd_codons_generate(&c, &g, 0);

  REQUIRE(0 == strcmp(s, "cos(y)"));

  rd_grammar_free(&g);
  rd_codons_free(&c);
  free(s);
}

TEST_CASE("Generate strings from grammar", "codons") {
  // <expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>
  // <op>   ::= * | + | - | /
  // <fun1> ::= sin | cos | exp
  // <var>  ::= x | y
  // <num>  ::= 0 | 1 | 2 | 3 | 4
  const char* str = "<expr> ::= <expr> <op> <expr> | (<expr><op><expr>) | <fun1>(<expr>) | <var> | <num>\n<op>   ::= * | + | - | /\n<fun1> ::= sin | cos | exp\n<var>  ::= x | y\n<num>  ::= 0 | 1 | 2 | 3 | 4";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);

  rd_codons c;
  rd_codons_init(&c, 6);
  c.codons[0] = 5;
  c.codons[1] = 3;
  c.codons[2] = 0;
  c.codons[3] = 0;
  c.codons[4] = 3;
  c.codons[5] = 0;

  char* s = rd_codons_generate(&c, &g, 0);

  REQUIRE(0 == strcmp(s, "x * x"));

  rd_grammar_free(&g);
  rd_codons_free(&c);
  free(s);
}

TEST_CASE("Generate complex strings from grammar", "codons") {
  // <expr>    ::= <expr> <op> <expr>
  //             | <pre-op><expr>
  //             | <fun1>(<expr)
  //             | <fun2>(<expr>, <expr>)
  //             | <var>
  // <op>      ::= + | - | / | *
  // <pre-op>  ::= -
  // <fun1>    ::= sin | cos | tan
  // <fun2>    ::= fmod
  // <var>     ::= x | y
  const char* str = "<expr>    ::= <expr> <op> <expr>\n | <pre-op><expr> \n| <fun1>(<expr>) \n| <fun2>(<expr>, <expr>)\n| <var>\n<op>      ::= + | - | / | *\n<pre-op>  ::= -\n<fun1>    ::= sin | cos | tan\n<fun2>    ::= fmod\n<var>     ::= x | y";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);

  rd_codons c;
  rd_codons_init(&c, 100);
  c.codons[0] = 0;
  c.codons[1] = 5;
  c.codons[2] = 7;
  c.codons[3] = 0;
  c.codons[4] = 8;
  c.codons[5] = 6;
  c.codons[6] = 8;
  c.codons[7] = 1;
  c.codons[8] = 4;
  c.codons[9] = 2;
  c.codons[10] = 8;
  c.codons[11] = 9;
  c.codons[12] = 6;
  c.codons[13] = 0;
  c.codons[14] = 4;
  c.codons[15] = 9;
  c.codons[16] = 6;
  c.codons[17] = 3;
  c.codons[18] = 1;
  c.codons[19] = 4;
  c.codons[20] = 8;
  c.codons[21] = 0;
  c.codons[22] = 7;
  c.codons[23] = 0;
  c.codons[24] = 9;
  c.codons[25] = 3;
  c.codons[26] = 9;
  c.codons[27] = 9;
  c.codons[28] = 5;
  c.codons[29] = 9;
  c.codons[30] = 4;
  c.codons[31] = 6;
  c.codons[32] = 8;
  c.codons[33] = 7;
  c.codons[34] = 0;
  c.codons[35] = 4;
  c.codons[36] = 2;
  c.codons[37] = 7;
  c.codons[38] = 6;
  c.codons[39] = 7;
  c.codons[40] = 4;
  c.codons[41] = 1;
  c.codons[42] = 5;
  c.codons[43] = 9;
  c.codons[44] = 5;
  c.codons[45] = 7;
  c.codons[46] = 2;
  c.codons[47] = 8;
  c.codons[48] = 1;
  c.codons[49] = 4;
  c.codons[50] = 6;
  c.codons[51] = 6;
  c.codons[52] = 9;
  c.codons[53] = 4;
  c.codons[54] = 6;
  c.codons[55] = 0;
  c.codons[56] = 5;
  c.codons[57] = 2;
  c.codons[58] = 5;
  c.codons[59] = 7;
  c.codons[60] = 3;
  c.codons[61] = 5;
  c.codons[62] = 7;
  c.codons[63] = 5;
  c.codons[64] = 9;
  c.codons[65] = 1;
  c.codons[66] = 9;
  c.codons[67] = 8;
  c.codons[68] = 9;
  c.codons[69] = 3;
  c.codons[70] = 5;
  c.codons[71] = 3;
  c.codons[72] = 3;
  c.codons[73] = 7;
  c.codons[74] = 5;
  c.codons[75] = 9;
  c.codons[76] = 8;
  c.codons[77] = 4;
  c.codons[78] = 1;
  c.codons[79] = 8;
  c.codons[80] = 4;
  c.codons[81] = 5;
  c.codons[82] = 4;
  c.codons[83] = 3;
  c.codons[84] = 1;
  c.codons[85] = 7;
  c.codons[86] = 9;
  c.codons[87] = 6;
  c.codons[88] = 0;
  c.codons[89] = 3;
  c.codons[90] = 5;
  c.codons[91] = 8;
  c.codons[92] = 6;
  c.codons[93] = 0;
  c.codons[94] = 3;
  c.codons[95] = 4;
  c.codons[96] = 0;
  c.codons[97] = 5;
  c.codons[98] = 7;
  c.codons[99] = 5;

  char* s = rd_codons_generate(&c, &g, 0);

  REQUIRE(0 == strcmp(s, "sin(fmod(-fmod(-x, fmod(x, y / fmod(-x, sin(y) - y))), x)) / fmod(sin(x), sin(cos(-y * tan(-x)))) / x"));

  rd_grammar_free(&g);
  rd_codons_free(&c);
  free(s);
}

TEST_CASE("Generate simple strings from grammar [blog example]", "codons") {
  // <cfun> ::= double please_work(double x, double y) { return <expr>; }
  // <expr> ::= <expr> <op> <expr>
  //          | <pre><expr>
  //          | <fun1>(<expr>)
  //          | <fun2>(<expr>, <expr>)
  //          | <var>
  // <op>   ::= + | - | / | *
  // <pre>  ::= -
  // <fun1> ::= sin | cos | tan
  // <fun2> ::= fmod
  // <var>  ::= x | y
  const char* str = "<cfun> ::= double please_work(double x, double y) { return <expr>; }\n<expr> ::= <expr> <op> <expr>\n         | <pre><expr>\n         | <fun1>(<expr>)\n         | <fun2>(<expr>, <expr>)\n         | <var>\n<op>   ::= + | - | / | *\n<pre>  ::= -\n<fun1> ::= sin | cos | tan\n<fun2> ::= fmod\n<var>  ::= x | y";
  rd_grammar g;
  rd_grammar_init_from_str(&g, str, NULL);

  rd_codons c;
  rd_codons_init(&c, 9);
  c.codons[0] = 10;
  c.codons[1] = 1;
  c.codons[2] = 2;
  c.codons[3] = 6;
  c.codons[4] = 9;
  c.codons[5] = 4;
  c.codons[6] = 0;
  c.codons[7] = 4;
  c.codons[8] = 7;

  char* s = rd_codons_generate(&c, &g, 0);
  REQUIRE(0 == strcmp(s, "double please_work(double x, double y) { return -sin(x) + y; }"));

  rd_grammar_free(&g);
  rd_codons_free(&c);
  free(s);
}
