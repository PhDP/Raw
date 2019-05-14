/**
 * @file grammar.h
 * @brief Structures to define the grammar.
 */
#ifndef RANDAMU_GRAMMAR_H_
#define RANDAMU_GRAMMAR_H_

#include "randamu/common.h"
#include "randamu/parsing_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief An alternative in a production rule represented as an ordered vector of strings.
 *
 * For example in the grammar:
 *
 * <expr>   ::= <number> | <expr> <op> <expr>
 * <op>     ::= + | -
 * <number> ::= 0 | 1 | 2 | 3 | 4 | 5
 *
 * The alternative "<expr> <op> <expr>" has 5 elements including the white spaces around
 * <op>.
 */
typedef struct {
  char** elems;
  size_t nmemb;
} rd_alt;

/**
 * @brief A production rule as a name and a series of alternatives.
 *
 * For example in:
 *
 * <expr> ::= 0 | 1 | !<expr>
 *
 * The production rule named <expr> has three alternatives: 0, 1, and !<expr>.
 */
typedef struct {
  char* name;
  rd_alt* alts;
  size_t nmemb;
} rd_production_rule;

/**
 * @brief ...
 */
typedef struct rd_grammar {
  rd_production_rule* rules; // Rules sorted by their name
  //a_rule_index* index; // Sorted vector of production names to their index in 'rules'
  size_t nmemb; // Number of production rules
} rd_grammar;

/**
 * @brief ...
 */
void rd_grammar_init_from_str(rd_grammar* g, const char* txt, rd_parsing_err* err);

/**
 * @brief ...
 */
void rd_grammar_init_from_file(rd_grammar* g, const char* filename, rd_parsing_err* err);

/**
 * @brief Returns the index of the rule with a given name. Linear complexity.
 * @return Returns the index or -1 if it wasn't found.
 */
int64_t rd_grammar_rule_idx(const rd_grammar* g, const char* rule);

/**
 * @brief Number of vertices in the grammar tree.
 */
size_t rd_grammar_complexity(const rd_grammar* g);

/**
 * @brief Prints the grammar 'g' to 'out'.
 */
void rd_grammar_show(const rd_grammar* g, FILE* out);

/**
 * @brief A less standard but more explicit representation of the grammar.
 */
void rd_grammar_show_details(const rd_grammar* g, FILE* out);

/**
 * @brief Frees memory for the grammar.
 */
void rd_grammar_free(rd_grammar* g);

#ifdef __cplusplus
}
#endif

#endif
