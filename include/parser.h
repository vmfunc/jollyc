#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "token.h"
#include "lexer.h"

#define MAX_VARIABLES 100

typedef struct {
    FILE* output_file;
    Token current_token;
    int indent_level;
    char variables[MAX_VARIABLES][MAX_TOKEN_LEN];
    int variable_count;
} Parser;

Parser* parser_create(FILE* output_file);
void parser_destroy(Parser* parser);
void parser_generate_code(Parser* parser, Lexer* lexer);

#endif 