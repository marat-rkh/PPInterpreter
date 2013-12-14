#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"
#include "parser.h"

using namespace std;

void PrintTokens(vector<Token>& tokens);

int main() {
    Lexer lexer;
//    string test_file = "../../tests/test_parser1";
//    string test_file = "../../tests/test_arithm_expr1";
    string test_file = "../../tests/test_parser2";
//    string test_file = "../../tests/test_lexer1";
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
        cout << "Parsing successfuly proceeded! = )" << endl;
    }
    return 0;
}

void PrintTokens(vector<Token>& tokens) {
    int counter = 1;
    cout << 1 << ' ';
    for(size_t i = 0; i != tokens.size(); ++i) {
        string tok_val = (tokens[i]).value_;
        if(tok_val == "\n") {
            cout << '\n' << ++counter << ' ';
        }
        else {
            cout << (tokens[i]).value_ << ' ';
        }
    }
    cout << endl;
}
