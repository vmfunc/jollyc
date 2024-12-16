#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

static int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

Lexer* lexer_create(const char* source) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->source = strdup(source);
    lexer->position = 0;
    lexer->length = strlen(source);
    return lexer;
}

void lexer_destroy(Lexer* lexer) {
    free(lexer->source);
    free(lexer);
}

void lexer_skip_whitespace(Lexer* lexer) {
    while (lexer->position < lexer->length && 
           is_whitespace(lexer->source[lexer->position])) {
        lexer->position++;
    }
}

Token lexer_next_token(Lexer* lexer) {
    Token token;
    char buffer[MAX_TOKEN_LEN];
    int buf_pos = 0;
    
    lexer_skip_whitespace(lexer);
    
    if (lexer->position >= lexer->length) {
        token.type = EOF_TOKEN;
        return token;
    }

    // Handle string literals
    if (lexer->source[lexer->position] == '"') {
        lexer->position++; // Skip opening quote
        while (lexer->position < lexer->length && 
               lexer->source[lexer->position] != '"' && 
               buf_pos < MAX_TOKEN_LEN - 1) {
            buffer[buf_pos++] = lexer->source[lexer->position++];
        }
        if (lexer->source[lexer->position] == '"') {
            lexer->position++; // Skip closing quote
        }
        buffer[buf_pos] = '\0';
        token.type = TINSEL;
        strcpy(token.value, buffer);
        return token;
    }
    
    // Read word
    while (lexer->position < lexer->length && 
           !is_whitespace(lexer->source[lexer->position]) && 
           buf_pos < MAX_TOKEN_LEN - 1) {
        buffer[buf_pos++] = lexer->source[lexer->position++];
    }
    buffer[buf_pos] = '\0';
    
    // Match keywords
    if (strcmp(buffer, "santa") == 0) token.type = SANTA;
    else if (strcmp(buffer, "rudolph") == 0) token.type = RUDOLPH;
    else if (strcmp(buffer, "presents") == 0) token.type = PRESENTS;
    else if (strcmp(buffer, "sleigh") == 0) token.type = SLEIGH;
    else if (strcmp(buffer, "reindeer") == 0) token.type = REINDEER;
    else if (strcmp(buffer, "mistletoe") == 0) token.type = MISTLETOE;
    else if (strcmp(buffer, "star") == 0) token.type = STAR;
    else if (strcmp(buffer, "bell") == 0) token.type = BELL;
    else if (strcmp(buffer, "wreath") == 0) token.type = WREATH;
    else {
        // Check if number
        int is_number = 1;
        for (int i = 0; buffer[i]; i++) {
            if (!isdigit(buffer[i])) {
                is_number = 0;
                break;
            }
        }
        token.type = is_number ? HOLLY : TINSEL;
    }
    
    strcpy(token.value, buffer);
    return token;
} 