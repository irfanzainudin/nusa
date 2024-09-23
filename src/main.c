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

    // Read source code file into a buffer
    char* contents = 0;
    long length;
    FILE* filename = fopen (argv[1], "rb");
    // TODO: Implement error handling for fseek, ftell, fread
    if (filename) {
        // TODO: May cause future problems as it may be Undefined Behaviour: https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c#comment81351612_174552
        fseek(filename, 0, SEEK_END);
        length = ftell(filename);
        fseek(filename, 0, SEEK_SET);
        contents = malloc(length + 1);
        if (contents)
        {
            fread(contents, 1, length, filename);
        }
        fclose(filename);
        contents[length] = '\0';
    } else {
        fprintf(stderr, "FAILED TO OPEN FILE\n");
        exit(1);
    }

    if (contents) {
        lexer_T* lexer = init_lexer(contents);
        // lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
        // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");

        parser_T* parser = init_parser(lexer);
        AST_T* root = parse(parser);
        // print_ast_type(root->type);
        // printf("root->compound_size: %lu\n", root->compound_size);
        // printf("root->compound_value[0]->variable_name: %s\n", root->compound_value[0]->variable_name);
        // printf("root->compound_value[1]->variable_name: %s\n", root->compound_value[1]->variable_name);
        // printf("root->function_call_args_size: %lu\n", root->function_call_args_size);
        // printf("root->function_call_name: %s\n", root->function_call_name);

        tokenise(argv[1], lexer);
        // tokenise_p(argv[1], parser);
    }
    
    free(contents);
    fclose(filename);
    return 0;
}