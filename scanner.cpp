#include <iostream>
#include <vector>
#include "scanner.h"

using namespace std;

class Scanner {
    public:

        string one_char_tokens = "()[]{}.;:=";
        TokenType types[10] = {T_LEFT_PAREN, T_RIGHT_PAREN, T_LEFT_BRACKET, T_RIGHT_BRACKET, T_LEFT_BRACE, T_RIGHT_BRACE, T_DOT, T_SEMI_COLON, T_COLON, T_EQUALS};

        string operators = "+-*/";
        TokenType operator_types[12] = {T_PLUS, T_MINUS,T_TIMES, T_DIVIDE, T_PLUS_PLUS, T_MINUS_MINUS, T_TIMES_TIMES, T_DIVIDE_DIVIDE, T_PLUS_EQUALS, T_MINUS_EQUALS, T_TIMES_EQUALS, T_DIVIDE_EQUALS};

        int lineno = 1;

        char next(string code, int pos) {
            if (pos + 1 >= code.length()) {
                return '_';
            }
            return code[pos + 1];
        }

        Token new_token(int type, string value, int col, int lineno, string line) {
            Token token;
            token.type = type;
            token.value = value;
            token.col = col;
            token.lineno = lineno;
            token.line = line;
            return token;
        }

        vector<Token> scan(string code) {
            vector<Token> tokens;
            int pos = 0;
            while (pos < code.length()) {
                char ch = code[pos];

                if (isdigit(ch)) {
                    string num;

                    int begin = pos;
                    while (isdigit(ch)) { // keep going until digit stops
                        num += ch;
                        ch = code[++pos];
                    }

                    tokens.push_back(new_token(T_INT, num, begin, lineno, code));
                }

                else if (isalpha(ch) || ch == '_') {
                    string name;

                    int begin = pos;
                    while (isalnum(ch) || ch == '_') { // keep going until name stops
                        name += ch;
                        ch = code[++pos];
                    }

                    if (name == "int" || name == "string") {
                        tokens.push_back(new_token(T_TYPE, name, begin, lineno, code));
                        continue;
                    }
                    tokens.push_back(new_token(T_ID, name, begin, lineno, code));
                }

                else if (ch == '"' || ch == '\'') {
                    string str;
                    char delimiter = ch; // either ' or "
                    int found_d = 0;

                    int begin = pos;
                    ch = code[++pos];
                    for (;;) { // keep going until found ending quote
                        if (ch == delimiter || pos >= code.length()) {
                            found_d = 1;
                            if (!found_d) {
                                string err = "Unexpected end of input";
                                cout << err;
                                throw(err);
                            }
                            break;
                        }
                        str += ch;
                        ch = code[++pos];
                    }

                    tokens.push_back(new_token(T_STR, str, begin, lineno, code));
                    pos++; // step over the ending quote
                }

                else if (one_char_tokens.find(ch) < one_char_tokens.length()) {
                    string strch(1, ch);
                    tokens.push_back(new_token(types[one_char_tokens.find(ch)], strch, pos + 1, lineno, code));
                    pos++;
                }

                else if (operators.find(ch) < operators.length()) {
                    string strch(1, ch);
                    if (next(code, pos) == ch) {
                        tokens.push_back(new_token(operator_types[operators.find(ch)+4], strch+strch, pos + 1, lineno, code));
                        pos += 2;
                    } else if (next(code, pos) == '=') {
                        tokens.push_back(new_token(operator_types[operators.find(ch)+8], strch+"=", pos + 1, lineno, code));
                        pos += 2;
                    } else {
                        tokens.push_back(new_token(operator_types[operators.find(ch)], strch, pos + 1, lineno, code));
                        pos++;
                    }
                }

                else if (ch == ' ' || ch == '\t') {
                    pos++;
                }

                else if (ch == '\n') {
                    pos++;
                    lineno++;
                }

                else {
                    string strch(1, ch);
                    string UnexpectedChar = "\nOn line " + to_string(lineno)+"\nUnexpected character `" + strch+"`\n" + code + "\n" + (string(pos, ' ') + '^');
                    cout << UnexpectedChar;
                    throw(UnexpectedChar);
                }
            }
            return tokens;
        }
};
