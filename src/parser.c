#include <stdio.h>
#include "include/parser.h"

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    // parser->scope = init_scope();

    return parser;
}

void parser_eat(parser_T* parser, int token_type) {
    if (parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Unexpected token `%s`, with type %d",
            parser->current_token->value,
            parser->current_token->type
        );
        exit(1);
    }
}

AST_T* parse(parser_T* parser) {
    return parse_statements(parser);
}

AST_T* parse_statement(parser_T* parser) {
    switch (parser->current_token->type)
    {
    case TOKEN_ID:
        return parse_id(parser);
        break;
    
    default:
        break;
    }
}

AST_T* parse_statements(parser_T* parser) {
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_statement = parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    // compound->compound_size += 1;

    while (parser->current_token->type == TOKEN_SEMI) {
        parser_eat(parser, TOKEN_SEMI);
        
        AST_T* ast_statement = parse_statement(parser);
        
        compound->compound_size += 1;
        compound->compound_value = realloc(
            compound->compound_value,
            compound->compound_size * sizeof(struct AST_STRUCT*)
        );
        compound->compound_value[compound->compound_size - 1] = ast_statement;
    }

    return compound;
}

AST_T* parse_expression(parser_T* parser) {
    switch (parser->current_token->type)
    {
    case TOKEN_STRING:
        return parse_string(parser);
        break;
    
    default:
        break;
    }
}

AST_T* parse_factor(parser_T* parser) {}

AST_T* parse_term(parser_T* parser) {}

AST_T* parse_function_call(parser_T* parser) {
    printf("yup!\n");
}

AST_T* parse_variable_definition(parser_T* parser) {
    parser_eat(parser, TOKEN_ID); // set
    char* variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_EQUALS);

    AST_T* variable_value = parse_expression(parser);
    AST_T* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_name = variable_name;
    variable_definition->variable_definition_value = variable_value;

    return variable_definition;
}

AST_T* parse_variable(parser_T* parser) {
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);
    
    if (parser->current_token->type == TOKEN_LPAREN)
        // return parse_function_call(parser, scope);
        return parse_function_call(parser);

    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;

    // ast_variable->scope = scope;

    return ast_variable;
}

AST_T* parse_string(parser_T* parser) {
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;
    
    parser_eat(parser, TOKEN_STRING);

    return ast_string;
}

AST_T* parse_id(parser_T* parser) {
    if (strcmp(parser->current_token->value, "set") == 0) {
        return parse_variable_definition(parser);
    } else {
        return parse_variable(parser);
    }
}