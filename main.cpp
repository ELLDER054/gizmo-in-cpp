#include <iostream>
#include "scanner.h"
#include "scanner.cpp"
#include "parser.cpp"

using namespace std;


int main() {
    try {
        Lexer lexer;
        vector<Token> tokens = lexer.lex("int a;");
        Parser parser;
        ProgramNode ast = parser.parse(tokens);
    }
    catch (string err) {
        cout << err <<'\n';
    }
}
