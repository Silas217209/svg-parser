#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>

enum TokenType {
    TOK_EOF = 0,
    TOK_ERROR,

    // Basic structural tokens
    TOK_OPEN,         // <
    TOK_CLOSE,        // >
    TOK_SLASH_CLOSE,  // />
    TOK_OPEN_SLASH,   // </
    TOK_EQUALS,       // =

    // Content
    TOK_STRING,  // Attribute values
    TOK_TEXT,    // Text content between tags, identifiers

    TOK_WHITESPACE,  // Whitespace

    // Processing instruction (for <?xml...?>)
    TOK_PI_START,  // <?
    TOK_PI_END,    // ?>

    // Comments (optional)
    TOK_COMMENT,  // includes entire comment, <!-- some comment -->
};

enum TokenType next_token(FILE* stream);

char* get_token_type(enum TokenType token);

#endif  // !TOKENIZER_H
