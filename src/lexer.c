#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "include/lexer.h"

lexer_T* init_lexer(char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->index = 0;
    lexer->current_char = contents[lexer->index];

    return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    // printf("lexer->current_char: %c\n", lexer->current_char);
    if (lexer->current_char != '\0' && lexer->index < strlen(lexer->contents)) {
        lexer->index++;
        lexer->current_char = lexer->contents[lexer->index];
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while (lexer->current_char == ' ' || lexer->current_char == '\n') {
        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    // printf("lexer->current_char: %s\n", lexer->current_char);
    while (lexer->current_char != '\0' && lexer->index < strlen(lexer->contents)) {
        if (lexer->current_char == ' ' || lexer->current_char == '\n') {
            lexer_skip_whitespace(lexer);
        }

        if (isalnum(lexer->current_char)) {
            return lexer_collect_id(lexer);
        }

        if (lexer->current_char == '"') {
            return lexer_collect_string(lexer);
        }

        if (lexer->current_char == "/") {
            return lexer_ignore_comment(lexer);
        }

        switch (lexer->current_char)
        {
        case '=': return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))); break;
        case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); break;
        case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
        case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
        case '{': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer))); break;
        case '}': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer))); break;
        case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))); break;
        case '/':
            return lexer_ignore_comment(lexer);
            break;
        
        default:
            break;
        }
    }

    return (void*)0;
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    lexer_advance(lexer); // ignore opening quote char

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    
    while (lexer->current_char != '"')
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strncat(value, s, strlen(value) + strlen(s));

        lexer_advance(lexer);
    }
    
    lexer_advance(lexer); // ignore closing quote char

    return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    
    while (isalnum(lexer->current_char))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strncat(value, s, strlen(value) + strlen(s));

        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

token_T* lexer_ignore_comment(lexer_T* lexer)
{
    lexer_advance(lexer); // skip '/' char
    lexer_advance(lexer); // skip '/' char

    while (lexer->current_char != '\n')
    {
        // if (lexer->current_char == EOF) // this doesn't work
        if (lexer->current_char == '\0') // TODO: why not EOF?
        {
            break;
        }
        lexer_advance(lexer);
    }

    return init_token(TOKEN_COMMENT, "");
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->current_char;
    str[1] = '\0';

    return str;
}