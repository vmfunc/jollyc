#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "compiler.h"

#define MAX_PROGRAM_LEN 10000

void error(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_c_file> <output_executable>\n", argv[0]);
        return 1;
    }

    // Read input file
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        error("Cannot open input file");
    }

    char* program = malloc(MAX_PROGRAM_LEN);
    int program_len = fread(program, 1, MAX_PROGRAM_LEN - 1, input_file);
    program[program_len] = '\0';
    fclose(input_file);

    // Create lexer
    Lexer* lexer = lexer_create(program);

    // Open output file
    FILE* output_file = fopen(argv[2], "w");
    if (!output_file) {
        error("Cannot open output file");
    }

    // Create parser and generate code
    Parser* parser = parser_create(output_file);
    parser_generate_code(parser, lexer);

    // Clean up
    parser_destroy(parser);
    lexer_destroy(lexer);
    free(program);
    fclose(output_file);

    // Compile the generated C code
    if (!compile_output(argv[2], argv[3])) {
        error("Compilation failed");
    }

    printf("Program successfully compiled. Run with: ./%s\n", argv[3]);
    return 0;
} 