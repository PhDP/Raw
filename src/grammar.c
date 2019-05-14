#include "randamu/grammar.h"
#include "randamu/str.h"

static int64_t skip_ws(const char* txt, int64_t curr) {
  while(txt[curr] != '\0' && (txt[curr] == ' ' || txt[curr] == '\n' || txt[curr] == '\t')) {
    ++curr;
  }
  return txt[curr] == '\0'? -1 : curr;
}

static int64_t parse_alt(rd_alt* a, const char* txt, int64_t curr) {
  curr = skip_ws(txt, curr);
  a->elems = NULL;
  a->nmemb = 0;
  if (txt[curr] == '\0' || txt[curr] == '|') {
    return curr;
  }
  size_t capacity = 8;
  a->elems = (char**)calloc(capacity, sizeof(char*)); // Remember to free in case of failure!

  while (txt[curr] != '\0' && txt[curr] != '|' && txt[curr] != '\n') {
    int64_t begin = curr;
    // Handles white spaces:
    if (txt[curr] == ' ') {
      while (txt[curr] == ' ') {
        ++curr;
      }
    // Handles production rules <...> and standard terminals:
    } else {
      const char c = txt[curr++] == '<'? '>' : ' ';
      while (txt[curr] != c && txt[curr] != '\0' && txt[curr] != '\n' && txt[curr] != '|' && txt[curr] != '<') {
        ++curr;
      }
      curr += (txt[curr] == c && c == '>');
    }
    const size_t length = curr - begin;
    if (a->nmemb == capacity) {
      capacity = (3 * capacity) >> 1;
      a->elems = (char**)realloc(a->elems, capacity * sizeof(char*));
    }
    a->elems[a->nmemb] = (char*)calloc(length + 1, 1);
    size_t i = 0;
    for (; i < length; ++i) {
      a->elems[a->nmemb][i] = txt[begin + i];
    }
    a->nmemb++;
  }

  // Remove the last element if it is the whitespaces between the alternative and the | operator:
  if (a->nmemb) {
    int last_is_ws = 1;
    char* c = a->elems[a->nmemb - 1];
    for (; *c != '\0'; ++c) {
      if (*c != ' ') {
        last_is_ws = 0;
        break;
      }
    }
    if (last_is_ws) {
      a->nmemb--;
      free(a->elems[a->nmemb]);
    }
  }
  return curr;
}

static int64_t parse_production_rule(rd_production_rule* r, const char* txt, int64_t curr) {
  curr = skip_ws(txt, curr);
  if (txt[curr] != '<') {
    return -1;
  }
  int64_t begin = curr;
  while (txt[curr] != '\0' && txt[curr] != '>') {
    ++curr;
  }
  ++curr;
  const size_t length = curr - begin;
  r->name = (char*)calloc(length + 1, 1);
  size_t i = 0;
  for (; i < length; ++i) {
    r->name[i] = txt[begin + i];
  }
  curr = skip_ws(txt, curr);

  if (txt[curr] == '\0' || txt[curr] != ':' || txt[++curr] == '\0' || txt[curr] != ':'
      || txt[++curr] == '\0' || txt[curr++] != '=') {
    return -1;
  }

  size_t alt_capacity = 8;
  r->nmemb = 0;
  r->alts = (rd_alt*)calloc(alt_capacity, sizeof(rd_alt));

  for (;;) {
    curr = parse_alt(&r->alts[r->nmemb], txt, curr);
    if (r->alts[r->nmemb].nmemb) {
      r->nmemb++;
      if (r->nmemb + 1 <= alt_capacity) {
        alt_capacity = (3 * alt_capacity) >> 1;
        r->alts = (rd_alt*)realloc(r->alts, alt_capacity * sizeof(rd_alt));
      }
      curr = skip_ws(txt, curr);
      if (txt[curr] == '|') {
        ++curr;
      } else {
        break;
      }
    } else {
      break;
    }
  }

  return curr;
}

void rd_grammar_init(rd_grammar* g) {
  g->nmemb = 0;
  g->rules = (rd_production_rule*)calloc(8, sizeof(rd_production_rule));
}

void rd_grammar_init_from_str(rd_grammar* g, const char* txt, rd_parsing_err* err) {
  rd_grammar_init(g);
  size_t rule_capacity = 8;
  int64_t idx = 0;
  while (idx != -1) {
    idx = parse_production_rule(&g->rules[g->nmemb], txt, idx);
    if (g->rules[g->nmemb].nmemb != 0) {
      g->nmemb++;
    } else {
      break;
    }
    if (g->nmemb + 1 <= rule_capacity) {
      rule_capacity = (3 * rule_capacity) >> 1;
      g->rules = (rd_production_rule*)realloc((void*)g->rules, rule_capacity * sizeof(rd_production_rule));
    }
  }
}

void rd_grammar_init_from_file(rd_grammar* g, const char* filename, rd_parsing_err* err) {
  const char* txt = rd_read_file(filename);
  if (txt) {
    rd_grammar_init_from_str(g, txt, err);
  } else if (err) {
    err->msg = (char*)realloc((void*)err->msg, strlen(filename) + 50);
    sprintf(err->msg, "Failed to open file \"%s\"", filename);
  }
}

int64_t rd_grammar_rule_idx(const rd_grammar* g, const char* rule) {
  int64_t i = 0;
  for (; i < g->nmemb; ++i) {
    if (strcmp(g->rules[i].name, rule) == 0) {
      return i;
    }
  }
  return -1;
}

size_t rd_grammar_complexity(const rd_grammar* g) {
  size_t complexity = g->nmemb * 2; // Name of the rule + ::= operator
  size_t i = 0, a;
  for (; i < g->nmemb; ++i) {
    complexity += g->rules[i].nmemb - 1; // The | operators
    for (a = 0; a < g->rules[i].nmemb; ++a) {
      complexity += g->rules[i].alts[a].nmemb;
    }
  }
  return complexity;
}

// Print grammars:

static void show_alt(const rd_alt* a, FILE* out) {
  size_t i = 0;
  for (; i < a->nmemb; ++i) {
    fprintf(out, "%s", a->elems[i]);
  }
}

void rd_grammar_show(const rd_grammar* g, FILE* out) {
  size_t r = 0;
  for (; r < g->nmemb; ++r) {
    fprintf(out, "%s ::= ", g->rules[r].name);
    if (g->rules[r].nmemb) {
      show_alt(&g->rules[r].alts[0], out);
      size_t a = 1;
      for (; a < g->rules[r].nmemb; ++a) {
        fprintf(out, " | ");
        show_alt(&g->rules[r].alts[a], out);
      }
      fprintf(out, "\n");
    }
  }
}

static void show_alt_details(const rd_alt* a, FILE* out) {
  size_t i = 0;
  for (; i < a->nmemb; ++i) {
    fprintf(out, "    Member #%lu: \"%s\"\n", i, a->elems[i]);
  }
}

void rd_grammar_show_details(const rd_grammar* g, FILE* out) {
  size_t r = 0;
  for (; r < g->nmemb; ++r) {
    fprintf(out, "Rule %s:\n", g->rules[r].name);
    if (g->rules[r].nmemb) {
      size_t a = 0;
      for (; a < g->rules[r].nmemb; ++a) {
        fprintf(out, "  Alternative #%lu:\n", a);
        show_alt_details(&g->rules[r].alts[a], out);
      }
    }
  }
}

// Free memory:

static void alt_free(rd_alt* a) {
  if (a && a->elems) {
    size_t i = 0;
    for (; i < a->nmemb; ++i) {
      free(a->elems[i]);
    }
    free(a->elems);
  }
}
static void production_rule_free(rd_production_rule* r) {
  if (r) {
    size_t i = 0;
    for (; i < r->nmemb; ++i) {
      alt_free(&r->alts[i]);
    }
    free(r->alts);
  }
}

void rd_grammar_free(rd_grammar* g) {
  if (g && g->rules) {
    size_t i = 0;
    for (; i < g->nmemb; ++i) {
      production_rule_free(&g->rules[i]);
    }
    free(g->rules);
  }
}
