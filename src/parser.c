#include <stdio.h>
#include "include/parser.h"
#include "include/utils.h"

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    // parser->scope = init_scope();
    print_current_token(parser);

    return parser;
}

// TODO: change this to `parser_expect`
void parser_eat(parser_T* parser, int token_type) {
    if (parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Unexpected token `%s`, with type %d: %s\n",
            parser->current_token->value,
            parser->current_token->type,
            return_token_type(parser->current_token->type)
        );
        exit(1);
    }
}

AST_T* parse(parser_T* parser) {
    printf("in parse\n");
    return parse_statements(parser);
}

AST_T* parse_statement(parser_T* parser) {
    printf("in parse_statement\n");
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
    printf("in parse_statements\n");
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_statement = parse_statement(parser);
    compound->compound_value[0] = ast_statement;

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
    printf("in parse_expr\n");
    switch (parser->current_token->type)
    {
    case TOKEN_STRING:
        return parse_string(parser);
    case TOKEN_ID:
        return parse_id(parser);
    
    default:
        break;
    }
}

AST_T* parse_factor(parser_T* parser) {}

AST_T* parse_term(parser_T* parser) {}

AST_T* parse_function_call(parser_T* parser) {
    AST_T* function_call = init_ast(AST_FUNCTION_CALL);
    function_call->function_call_args = calloc(1, sizeof(struct AST_STRUCT*));
    function_call->function_call_name = parser->prev_token->value;
    printf("yup! %s\n", parser->prev_token->value);

    AST_T* ast_expr = parse_expression(parser);
    function_call->function_call_args[0] = ast_expr;

    while (parser->current_token->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);
        
        AST_T* ast_expr = parse_expression(parser);
        
        function_call->function_call_args_size += 1;
        function_call->function_call_args = realloc(
            function_call->function_call_args,
            function_call->function_call_args_size * sizeof(struct AST_STRUCT*)
        );
        function_call->function_call_args[function_call->function_call_args_size - 1] = ast_expr;
    }

    return function_call;
}

AST_T* parse_variable_definition(parser_T* parser) {
    printf("in parse_var_def\n");
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
    printf("in parse_var\n");
    printf("parser->current_token: %s\n", parser->current_token->value);
    printf("parser->current_token->type: %d\n", parser->current_token->type);
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); // eats `tolong`
    printf("parser->current_token: %s\n", parser->current_token->value);
    printf("parser->current_token->type after parser_eat: %d\n", parser->current_token->type);
    parser_eat(parser, TOKEN_ID); // eats `cetak`
    printf("parser->current_token: %s\n", parser->current_token->value);
    printf("parser->current_token->type after parser_eat: %d\n", parser->current_token->type);
    
    if (parser->current_token->type == TOKEN_LPAREN)
        // return parse_function_call(parser, scope);
        return parse_function_call(parser);

    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;

    // ast_variable->scope = scope;

    return ast_variable;
}

AST_T* parse_string(parser_T* parser) {
    printf("in parse_str\n");
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;
    
    parser_eat(parser, TOKEN_STRING);

    return ast_string;
}

AST_T* parse_id(parser_T* parser) {
    printf("in parse_id\n");
    if (strcmp(parser->current_token->value, "set") == 0) {
        return parse_variable_definition(parser);
    } else {
        return parse_variable(parser);
    }
}