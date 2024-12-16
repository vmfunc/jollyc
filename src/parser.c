#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"

Parser* parser_create(FILE* output_file) {
    Parser* parser = malloc(sizeof(Parser));
    parser->output_file = output_file;
    parser->indent_level = 0;
    return parser;
}

void parser_destroy(Parser* parser) {
    free(parser);
}

static void write_indentation(Parser* parser) {
    for (int i = 0; i < parser->indent_level; i++) {
        fprintf(parser->output_file, "    ");
    }
}

void parser_generate_code(Parser* parser, Lexer* lexer) {
    // Write C file header
    fprintf(parser->output_file, "#include <stdio.h>\n\n");
    
    parser->current_token = lexer_next_token(lexer);
    
    while (parser->current_token.type != EOF_TOKEN) {
        write_indentation(parser);
        
        switch (parser->current_token.type) {
            case SANTA:
                parser->current_token = lexer_next_token(lexer);
                fprintf(parser->output_file, "int %s() {\n", parser->current_token.value);
                parser->indent_level++;
                break;
                
            case RUDOLPH:
                fprintf(parser->output_file, "return 0;\n");
                break;
                
            case PRESENTS:
                parser->current_token = lexer_next_token(lexer);
                fprintf(parser->output_file, "int %s;\n", parser->current_token.value);
                break;
                
            case SLEIGH:
                parser->current_token = lexer_next_token(lexer);
                fprintf(parser->output_file, "for(int i = 0; i < %s; i++) {\n", 
                        parser->current_token.value);
                parser->indent_level++;
                break;
                
            case REINDEER:
                parser->current_token = lexer_next_token(lexer);
                fprintf(parser->output_file, "if(%s) {\n", parser->current_token.value);
                parser->indent_level++;
                break;
                
            case MISTLETOE:
                parser->indent_level--;
                write_indentation(parser);
                fprintf(parser->output_file, "} else {\n");
                parser->indent_level++;
                break;
                
            case STAR:
                parser->current_token = lexer_next_token(lexer);
                if (parser->current_token.type == TINSEL) {
                    fprintf(parser->output_file, "printf(\"%%s\\n\", \"%s\");\n", 
                            parser->current_token.value);
                } else {
                    fprintf(parser->output_file, "printf(\"%%d\\n\", %s);\n", 
                            parser->current_token.value);
                }
                break;
                
            case BELL:
                parser->indent_level--;
                fprintf(parser->output_file, "}\n");
                break;
                
            case WREATH:
                {
                    char var_name[MAX_TOKEN_LEN];
                    strcpy(var_name, parser->current_token.value);
                    parser->current_token = lexer_next_token(lexer);
                    fprintf(parser->output_file, "%s = %s;\n", var_name, 
                            parser->current_token.value);
                }
                break;
                
            default:
                break;
        }
        parser->current_token = lexer_next_token(lexer);
    }
    
    if (parser->indent_level > 0) {
        parser->indent_level--;
        write_indentation(parser);
        fprintf(parser->output_file, "}\n");
    }
} 