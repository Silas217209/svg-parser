#include "tokenizer.h"

#include <stdio.h>

enum TokenType get_tok_comment_start(FILE* stream) {
    int c1 = fgetc(stream);
    if (c1 != '-') {
        ungetc(c1, stream);
        return TOK_ERROR;
    }

    int c2 = fgetc(stream);
    if (c2 != '-') {
        ungetc(c1, stream);
        ungetc(c2, stream);
        return TOK_ERROR;
    }

    while (1) {
        int c3 = fgetc(stream);
        if (c3 == EOF) break;

        if (c3 != '-') continue;
        int c4 = fgetc(stream);
        if (c4 != EOF && c4 != '-') continue;
        int c5 = fgetc(stream);
        if (c5 != EOF && c5 == '>') break;
    }

    return TOK_COMMENT;
}

enum TokenType get_tok_open(FILE* stream) {
    int character = fgetc(stream);
    switch (character) {
        case '/':
            return TOK_OPEN_SLASH;
        case '?':
            return TOK_PI_START;
        case '!':
            return get_tok_comment_start(stream);
        default:
            ungetc(character, stream);
            return TOK_OPEN;
    }
}

enum TokenType get_tok_slash(FILE* stream) {
    int c = fgetc(stream);
    if (c == '>') return TOK_SLASH_CLOSE;
    return TOK_ERROR;
}

enum TokenType get_tok_question(FILE* stream) {
    int c = fgetc(stream);
    if (c == '>') return TOK_PI_END;
    return TOK_ERROR;
}

enum TokenType get_tok_string(FILE* stream, char quote) {
    int escape_next = 0;
    while (1) {
        int c = fgetc(stream);
        if (c == '\\') {
            escape_next = 1;
        } else if (!escape_next && c == quote) {
            break;
        }
    }
    return TOK_STRING;
}

enum TokenType get_tok_text(FILE* stream) {
    while (1) {
        int c = fgetc(stream);

        switch (c) {
            case '<':
            case 0x20:  // Space
            case 0x09:  // Horizontal tab
            case 0x0D:  // Carriage return
            case 0x0A:  // Line feed
            case '>':
            case '/':
            case '?':
            case '=':
            case '"':
            case '\'':
            case EOF:
                ungetc(c, stream);
                return TOK_TEXT;
            default:
                continue;
        }
    }
}

enum TokenType next_token(FILE* stream) {
    int character = fgetc(stream);

    switch (character) {
        case '<':
            return get_tok_open(stream);
        case 0x20:  // Space
        case 0x09:  // Horizontal tab
        case 0x0D:  // Carriage return
        case 0x0A:  // Line feed
            return TOK_WHITESPACE;
        case '>':
            return TOK_CLOSE;
        case '/':
            return get_tok_slash(stream);
        case '?':
            return get_tok_question(stream);
        case '=':
            return TOK_EQUALS;
        case '"':
            return get_tok_string(stream, '"');
        case '\'':
            return get_tok_string(stream, '\'');
        case EOF:
            return TOK_EOF;
        default:
            return get_tok_text(stream);
    }

    return TOK_ERROR;
}

char* get_token_type(enum TokenType token) {
    switch (token) {
        case TOK_EOF:
            return "TOK_EOF";
        case TOK_ERROR:
            return "TOK_ERROR";
        case TOK_OPEN:
            return "TOK_OPEN";
        case TOK_CLOSE:
            return "TOK_CLOSE";
        case TOK_SLASH_CLOSE:
            return "TOK_SLASH_CLOSE";
        case TOK_OPEN_SLASH:
            return "TOK_OPEN_SLASH";
        case TOK_EQUALS:
            return "TOK_EQUALS";
        case TOK_STRING:
            return "TOK_STRING";
        case TOK_TEXT:
            return "TOK_TEXT";
        case TOK_WHITESPACE:
            return "TOK_SPACE";
        case TOK_PI_START:
            return "TOK_PI_START";
        case TOK_PI_END:
            return "TOK_PI_END";
        case TOK_COMMENT:
            return "TOK_COMMENT";
        default:
            return "UNHALDED";
    }
}
