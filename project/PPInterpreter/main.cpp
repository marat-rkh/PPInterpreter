#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"
#include "parser.h"

#include "globalscope.h"
#include "program.h"
#include "error.h"

using namespace std;

void PrintTokens(vector<Token>& tokens);
void TestLexer(std::string test_file, bool print);
void TestParser(std::string test_file);
void TestEvaluation(std::string test_file);

int main() {
//    string test_file = "../../tests/test_parser1";
//    string test_file = "../../tests/test_arithm_expr1";
//    string test_file = "../../tests/test_parser2";
//    string test_file = "../../tests/test_lexer1";
    string test_file = "../../tests/test_eval1";

    TestLexer(test_file, false);
    TestParser(test_file);
    TestEvaluation(test_file);

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

void TestLexer(std::string test_file, bool print) {
    Lexer lexer;
    int res = lexer.Tokenize(test_file);
    if(res < 0) {
        cout << "Lexer: can't open file" << endl;
        return;
    }
    if(res > 0) {
        cout << "Lexer: lexing error at line: " << res << endl;
        return;
    }
    cout << "Lexer test successfully completed" << endl;
    if(print) {
        vector<Token> tokens = lexer.tokens();
        PrintTokens(tokens);
    }
}

void TestParser(std::string test_file) {
    Lexer lexer;
    lexer.Tokenize(test_file);
    Parser parser(lexer.tokens());
    Error error;
    parser.Parse(error);
    if(error.IsOccured()) {
        cout << error.GetErrorMessage() << endl;
        return;
    }
    cout << "Parse test successfully completed" << endl;
}

void TestEvaluation(std::string test_file) {
    Lexer lexer;
    lexer.Tokenize(test_file);
    Parser parser(lexer.tokens());
    Error error;
    Program program(parser.Parse(error));
    program.Evaluate(error);
    if(error.IsOccured()) {
        cout << error.GetErrorMessage() << endl;
        return;
    }
    cout << endl << "Evaluation test successfully completed" << endl;
}
