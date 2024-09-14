#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/lexer.h"
#include "include/readall.h"

#define MAX 100
#define MAX_FILENAME 1024

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "USAGE: %s <SOURCE_CODE_FILENAME>\n", argv[0]);
        exit(1);
    }
    
    // Check for the file's extension / format
    char src_code_filename[MAX_FILENAME];
    (void) strlcpy(src_code_filename, argv[1], sizeof(src_code_filename));
    strtok(src_code_filename, ".");
    if (strcmp(strtok(NULL, "."), "nusa") != 0)
    {
        printf("Supplied file is not a Nusa file!\n");
        printf(stderr, "Supplied file is not a Nusa file!\n");
        exit(1);
    }
    
    FILE* filename = fopen(argv[1], "r");
    if (filename == NULL)
    {
        fprintf(stderr, "FAILED TO OPEN FILE\n");
        exit(1);
    }
    // fseek(filename, 0, SEEK_END);
    // long fsize = ftell(filename);
    // fseek(filename, 0, SEEK_SET);  /* same as rewind(f); */

    char* contents = calloc(1, MAX);
    // fprintf(stdout, "%s", fgets(contents, MAX, filename));
    // char* contents = malloc(fsize + 1); // +1 for EOF char (I assume)
    // readall(filename, contents, &fsize);

    while (fgets(contents, MAX, filename)) {
        lexer_T* lexer = init_lexer(contents);
        // lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
        // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");

        token_T* token = (void*)0;
        while ((token = lexer_get_next_token(lexer)) != (void*)0) {
            printf("TOKEN(%d, %s)\n", token->type, token->value);
        }
    }
    
    free(contents);
    fclose(filename);
    return 0;
}