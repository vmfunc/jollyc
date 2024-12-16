#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKEN_LEN 256

typedef enum {
    SANTA,      // Function definition
    RUDOLPH,    // Return
    PRESENTS,   // Variables
    SLEIGH,     // Loop
    REINDEER,   // If condition
    MISTLETOE,  // Else
    STAR,       // Print
    HOLLY,      // Number literal
    TINSEL,     // String literal
    BELL,       // End block
    WREATH,     // Assignment
    QUOTE,      // String delimiter
    EOF_TOKEN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

#endif 