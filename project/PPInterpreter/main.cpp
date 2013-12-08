#include <iostream>
#include <vector>

#include "lexer.h"

using namespace std;

int main() {
    Lexer lexer;
    ssize_t res = lexer.Tokenize("../../tests/test_lexer1");
    if(res < 0) {
        cout << "can't open file" << endl;
        return 0;
    }
    if(res > 0) {
        cout << "lexing error at line: " << res << endl;
        return 0;
    }
    vector<Token> tokens = lexer.tokens();
    for(size_t i = 0; i != tokens.size(); ++i) {
        cout << (tokens[i]).value_ << endl;
    }
    return 0;
}
