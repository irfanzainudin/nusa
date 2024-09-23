#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utils.h"
#include "include/token.h"
#include "include/AST.h"

void print_help(char* src_file)
{
    fprintf(stderr, "USAGE: %s <SOURCE_CODE_FILENAME>\n", src_file);
}

void check_input_file(int argc, char* program_name, char* src_file)
{
    if (argc < 2)
    {
        fprintf(stderr, "USAGE: %s <SOURCE_CODE_FILENAME>\n", program_name);
        exit(1);
    }
    
    // Check for the file's extension / format
    char src_code_filename[MAX_FILENAME];
    (void) strlcpy(src_code_filename, src_file, sizeof(src_code_filename));
    strtok(src_code_filename, ".");
    if (strcmp(strtok(NULL, "."), "nusa") != 0)
    {
        fprintf(stderr, "Supplied file is not a Nusa file!\n");
        exit(1);
    }
}

void print_token_type_given_type_enum(size_t token_type) {
    switch (token_type)
    {
    case TOKEN_ID:
        printf("TOKEN_ID\n");
        break;
    case TOKEN_EQUALS:
        printf("TOKEN_EQUALS\n");
        break;
    case TOKEN_STRING:
        printf("TOKEN_STRING\n");
        break;
    case TOKEN_SEMI:
        printf("TOKEN_SEMI\n");
        break;
    case TOKEN_LPAREN:
        printf("TOKEN_LPAREN\n");
        break;
    case TOKEN_RPAREN:
        printf("TOKEN_RPAREN\n");
        break;
    case TOKEN_LBRACE:
        printf("TOKEN_LBRACE\n");
        break;
    case TOKEN_RBRACE:
        printf("TOKEN_RBRACE\n");
        break;
    case TOKEN_COMMA:
        printf("TOKEN_COMMA\n");
        break;
    case TOKEN_COMMENT:
        printf("TOKEN_COMMENT\n");
        break;
    case TOKEN_EOF:
        printf("TOKEN_EOF\n");
        break;
    
    default:
        break;
    }
}

void print_ast_type_given_type_enum(size_t ast_type) {
    switch (ast_type)
    {
    case AST_VARIABLE_DEFINITION:
        printf("AST_VARIABLE_DEFINITION\n");
        break;
    case AST_VARIABLE:
        printf("AST_VARIABLE\n");
        break;
    case AST_FUNCTION_CALL:
        printf("AST_FUNCTION_CALL\n");
        break;
    case AST_STRING:
        printf("AST_STRING\n");
        break;
    case AST_COMPOUND:
        printf("AST_COMPOUND\n");
        break;
    
    default:
        break;
    }
}

void print_token_type(size_t token_type)
{
    printf("%lu: ", token_type);
    print_token_type_given_type_enum(token_type);
}

char* return_token_type(size_t token_type)
{
    switch (token_type)
    {
    case TOKEN_ID:
        return "TOKEN_ID";
    case TOKEN_EQUALS:
        return "TOKEN_EQUALS";
    case TOKEN_STRING:
        return "TOKEN_STRING";
    case TOKEN_SEMI:
        return "TOKEN_SEMI";
    case TOKEN_LPAREN:
        return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
        return "TOKEN_RPAREN";
    case TOKEN_LBRACE:
        return "TOKEN_LBRACE";
    case TOKEN_RBRACE:
        return "TOKEN_RBRACE";
    case TOKEN_COMMA:
        return "TOKEN_COMMA";
    case TOKEN_COMMENT:
        return "TOKEN_COMMENT";
    case TOKEN_EOF:
        return "TOKEN_EOF";
    
    default:
        return "TOKEN_EOF"; // TODO: may pose a problem in the future
    }
}

void print_ast_type(size_t ast_type)
{
    printf("%lu: ", ast_type);
    print_ast_type_given_type_enum(ast_type);
}

char* return_ast_type(size_t ast_type)
{
    switch (ast_type)
    {
    case AST_VARIABLE_DEFINITION:
        return "AST_VARIABLE_DEFINITION";
    case AST_VARIABLE:
        return "AST_VARIABLE";
    case AST_FUNCTION_CALL:
        return "AST_FUNCTION_CALL";
    case AST_STRING:
        return "AST_STRING";
    case AST_COMPOUND:
        return "AST_COMPOUND";
    
    default:
        return "AST_COMPOUND"; // TODO: may pose a problem in the future
    }
}

void tokenise(char* src_file, lexer_T* lexer)
{
    printf("\n#########################################\n");
    printf("##### Tokens of %s #####\n", src_file);
    printf("#########################################\n");
    
    token_T* token = (void*)0;
    // NOTE: How do you compare structs for equality in C?
    // => https://stackoverflow.com/a/141724/9311041
    while ((token = lexer_get_next_token(lexer))->type != TOKEN_EOF) {
        printf("> TOKEN[%d: %s, %s]\n", token->type, return_token_type(token->type), token->value);
    }
}

void print_current_token(parser_T* parser)
{
    printf("%s: ", parser->current_token->value);
    printf("(%u) ", parser->current_token->type);
    print_token_type_given_type_enum(parser->current_token->type);
}