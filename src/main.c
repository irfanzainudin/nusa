#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/readall.h"

#define MAX 100
#define MAX_FILENAME 1024

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

int main(int argc, char* argv[])
{   
    // lexer_T* lexer = init_lexer("var name = \"john doe\";\n\nprint(name);");
    lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
    // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");
    
    parser_T* parser = init_parser(lexer);
    AST_T* root = parse(parser);
    printf("%s\n", root->type);

    // token_T* token = (void*)0;
    // while ((token = lexer_get_next_token(lexer)) != (void*)0) {
    //     printf("TOKEN(%d, %s)\n", token->type, token->value);
    // }
    
    /* check_input_file(argc, argv[0], argv[1]);
    
    FILE* filename = fopen(argv[1], "r");
    if (filename == NULL)
    {
        fprintf(stderr, "FAILED TO OPEN FILE\n");
        exit(1);
    }

    char* contents = calloc(1, MAX);

    while (fgets(contents, MAX, filename)) {
        // lexer_T* lexer = init_lexer(contents);
        // lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
        // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");

        // parser_T* parser = init_parser(lexer);
        // AST_T* root = parse(parser);

        // printf("%s\n", root->type);

        token_T* token = (void*)0;
        while ((token = lexer_get_next_token(lexer)) != (void*)0) {
            printf("TOKEN(%d, %s)\n", token->type, token->value);
        }
    }
    
    free(contents);
    fclose(filename); */
    return 0;
}