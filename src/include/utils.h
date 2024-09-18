#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include "lexer.h"

#define MAX 100
#define MAX_FILENAME 1024

void print_help(char* src_file);
void check_input_file(int argc, char* program_name, char* src_file);
void print_token_type_given_type_enum(size_t token_type);
void print_token_type(size_t token_type);
char* token_type(size_t ast_type);
void print_ast_type_given_type_enum(size_t ast_type);
void print_ast_type(size_t ast_type);
char* ast_type(size_t ast_type);
void tokenise(char* src_file, lexer_T* lexer);

#endif