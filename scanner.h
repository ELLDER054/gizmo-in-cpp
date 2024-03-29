#include <iostream>

#ifndef SCANNER_H
#define SCANNER_H

using namespace std;


typedef enum {
    T_INT = 200,
    T_REAL,
    T_STR,
    T_CHAR,

    // Identifiers
    T_ID,
    T_KEY,
    T_TYPE,
    T_BUILTIN,

    // Symbols
    T_LEFT_PAREN,
    T_RIGHT_PAREN,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    T_DOT,
    T_COMMA,
    T_COLON,
    T_SEMI_COLON,
    T_EQUALS,
    T_LESS_THAN,
    T_GREATER_THAN,
    T_LESS_THAN_EQUALS,
    T_GREATER_THAN_EQUALS,
    T_PLUS,
    T_PLUS_EQUALS,
    T_PLUS_PLUS,
    T_MINUS,
    T_MINUS_EQUALS,
    T_MINUS_MINUS,
    T_TIMES,
    T_TIMES_EQUALS,
    T_TIMES_TIMES,
    T_DIVIDE,
    T_DIVIDE_EQUALS,
    T_DIVIDE_DIVIDE,
    T_BEGIN_COMMENT,
    T_BEGIN_LINE_COMMENT,
    T_END_LINE_COMMENT,
} TokenType;

class Token {
    public:
        int type;
        string value;
        int col;
        string line;
        int lineno;

    ~Token() {
        // ?
    }
};

#endif
