#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include "lexer.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_T* lexer;
    token_T* current_token;
    token_T* prev_token;
    // scope_T* scope;
} parser_T;

parser_T* init_parser(lexer_T* lexer);
void parser_eat(parser_T* parser, int token_type);
AST_T* parse(parser_T* parser);
AST_T* parse_statement(parser_T* parser);
AST_T* parse_statements(parser_T* parser);
AST_T* parse_expression(parser_T* parser);
AST_T* parse_factor(parser_T* parser);
AST_T* parse_term(parser_T* parser);
AST_T* parse_function_call(parser_T* parser);
AST_T* parse_variable_definition(parser_T* parser);
AST_T* parse_variable(parser_T* parser);
AST_T* parse_string(parser_T* parser);
AST_T* parse_id(parser_T* parser);

#endif