#pragma once
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum type_t {
  t_END_OF_FILE = 0,
  t_UNKNOWN,
  t_DOUBLEQUOTE,
  t_RPAREN,
  t_LPAREN,
  t_QUOTE,
  t_QUASIQUOTE,
  t_UNQUOTE,
  t_NUMBER,
  t_ATOM,
  t_COMMENT,
  t_NEWLINE,
  t_TRUE,
  t_FALSE,
  t_DOT, // this should work in atom still
  t_ERROR,
};

typedef struct {
  enum type_t t;
  char *str;
  double num;
} prim_t;

void print_token(prim_t token);
char looking_at();
char advance();
void flush();
prim_t scan();

#define PARSE_CTX_BUFF_SIZE 1024

typedef struct {
  FILE *file;
  char buffer[PARSE_CTX_BUFF_SIZE];
  int buf_pos;
  int buf_end;
  char curr;
  bool once; // parse only one line
} parse_ctx;

parse_ctx *deep_copy_parse_ctx(const parse_ctx *src);
void switch_ctx_to_file(FILE *file);
void switch_ctx_to_stdin();
void switch_ctx_inject_string(const char *str);

#define TOKEN_BUFFER_SIZE 1024

typedef struct {
  prim_t buffer[TOKEN_BUFFER_SIZE];
  int idx;
} token_buffer_t;

#include "interpreter.h"

void reseti(token_buffer_t *tb);
prim_t look(token_buffer_t *tb);
prim_t get(token_buffer_t *tb);
prim_t next(token_buffer_t *tb);
prim_t prev(token_buffer_t *tb);
expr_t parse(interpreter_t *ctx, token_buffer_t *tb);
expr_t list(interpreter_t *ctx, token_buffer_t *tb);