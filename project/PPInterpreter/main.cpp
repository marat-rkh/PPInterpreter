#include <iostream>
#include <vector>

#include "lexer.h"
#include "parser.h"

using namespace std;

void PrintTokens(vector<Token>& tokens);

int main() {
    Lexer lexer;
    string test_file = "../../../../tests/test_parser1";
    int res = lexer.Tokenize(test_file);
    if(res < 0) {
        cout << "Lexer: can't open file" << endl;
        return 0;
    }
    if(res > 0) {
        cout << "Lexer: lexing error at line: " << res << endl;
        return 0;
    }
    vector<Token> tokens = lexer.tokens();
    PrintTokens(tokens);
    Parser parser(tokens);
    res = parser.Parse();
    if(res) {
        cout << "Parser: parsing error at line: " << res << endl;
    }
    else {
        cout << "Parsing successful! = )" << endl;
    }
	system("pause");
    return 0;
}

void PrintTokens(vector<Token>& tokens) {
    for(size_t i = 0; i != tokens.size(); ++i) {
        cout << (tokens[i]).value_ << ' ';
    }
}
