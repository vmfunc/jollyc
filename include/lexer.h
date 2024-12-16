#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    char* source;
    int position;
    int length;
} Lexer;

Lexer* lexer_create(const char* source);
void lexer_destroy(Lexer* lexer);
Token lexer_next_token(Lexer* lexer);
void lexer_skip_whitespace(Lexer* lexer);

#endif 