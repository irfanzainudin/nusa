#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/utils.h"
#include "include/readall.h"

int main(int argc, char* argv[])
{
    check_input_file(argc, argv[0], argv[1]);
    
    FILE* filename = fopen(argv[1], "r");
    if (filename == NULL)
    {
        fprintf(stderr, "FAILED TO OPEN FILE\n");
        exit(1);
    }

    char* contents = calloc(1, MAX);

    while (fgets(contents, MAX, filename)) {
        // lexer_T* lexer = init_lexer(contents);
        lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
        // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");

        parser_T* parser = init_parser(lexer);
        AST_T* root = parse(parser);
        print_ast_type(root->type);

        tokenise(argv[1], lexer);
    }
    
    free(contents);
    fclose(filename);
    return 0;
}