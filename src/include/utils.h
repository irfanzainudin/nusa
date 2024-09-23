#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include "lexer.h"
#include "parser.h"

#define MAX 100
#define MAX_FILENAME 1024

void print_help(char* src_file);
void check_input_file(int argc, char* program_name, char* src_file);
void print_token_type_given_type_enum(size_t token_type);
void print_token_type(size_t token_type);
char* return_token_type(size_t token_type);
void print_ast_type_given_type_enum(size_t ast_type);
void print_ast_type(size_t ast_type);
char* return_ast_type(size_t ast_type);
void tokenise(char* src_file, lexer_T* lexer);
void tokenise_p(char* src_file, parser_T* parser);
void print_current_token(parser_T* parser);

#endif