#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"

#define MAX 100

char** split(char* str_to_be_split, char* optional_delimiter)
{
    printf("%s\n", str_to_be_split);
    // char* delim = (optional_delimiter != NULL) ? optional_delimiter : ' ';
    // char** splitted = calloc(1, sizeof(char)); // TODO: 1 may pose future problems

    // int segment_index = 0;
    // char* segment = calloc(1, sizeof(char));
    char* curr = &str_to_be_split[0];
    printf("curr: %s\n", curr);
    // while (curr != '\0') {
    //     printf("curr: %s\n", curr);
    //     if (curr == delim) {
    //         splitted[segment_index] = &segment;
    //         segment_index++;
    //         segment = realloc(segment, 1 * sizeof(char));
    //     } else {
    //         strcat(segment, curr);
    //     }

    //     curr = str_to_be_split++;
    // }

    // return splitted;
    return NULL;
}

int main(int argc, char* argv[]) {
    // char s[100] = "salam.nusa";
    // char** sp = split(s, ".");
    // for (int i = 0; i < strlen(sp[0]); i++) {
    //     printf("%s", sp[i]);
    // }
    // if (argc < 2)
    // {
    //     fprintf(stderr, "USAGE: %s <SOURCE_CODE_FILENAME>\n", argv[0]);
    //     exit(1);
    // }
    
    // char* source_code_filename = argv[1];
    // printf("%s\n", source_code_filename);
    // Check for the file's extension / format
    // char* separated_src_code_filename = strtok(source_code_filename, ".");
    // printf("%s\n", separated_src_code_filename);
    // if (separated_src_code_filename[strlen(separated_src_code_filename - 1)] != "nusa")
    // {
    //     printf(stderr, "Not a Nusa file!");
    //     exit(1);
    // }
    
    // FILE* filename = fopen(source_code_filename, "r");
    // if (filename == NULL)
    // {
    //     fprintf(stderr, "FAILED TO OPEN FILE\n");
    //     exit(1);
    // }

    // char* contents = calloc(1, MAX);
    // fprintf(stdout, "%s", fgets(contents, MAX, filename));

    // lexer_T* lexer = init_lexer(contents);
    lexer_T* lexer = init_lexer("tolong cetak \"Salam, Nusa!\";\n");
    // lexer_T* lexer = init_lexer("set nama = \"irfanzainudin\";\ncetak nama;\n");

    token_T* token = (void*)0;

    while ((token = lexer_get_next_token(lexer)) != (void*)0) {
        printf("TOKEN(%d, %s)\n", token->type, token->value);
    }
    
    // free(contents);
    // fclose(filename);
    return 0;
}