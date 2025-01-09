#define _DEFAULT_SOURCE

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* source_path_raw = argv[1];

    char source_path[PATH_MAX];
    if (realpath(source_path_raw, source_path) == NULL) {
        fprintf(stderr, "Error resolving path: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    FILE* source_file = fopen(source_path, "r");
    while (1) {
        enum TokenType token = next_token(source_file);
        switch (token) {
            case TOK_ERROR:
                printf(".");
                break;
            case TOK_WHITESPACE:
                continue;
            case TOK_EOF:
                goto end;
            default:
                printf("\n%s", get_token_type(token));
                break;
        }
    }

end:
    printf("\n");
}
