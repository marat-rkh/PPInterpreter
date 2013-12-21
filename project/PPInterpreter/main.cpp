#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"
#include "parser.h"

#include "Visitables/program.h"
#include "evaluator.h"
#include "globalscope.h"
#include "error.h"

using std::cout;
using std::endl;
using std::vector;

void PrintTokens(vector<Token>& tokens);
void TestLexer(std::string test_file, bool print);
void TestParser(std::string test_file);
void TestEvaluation(std::string test_file);

int main(int argc, char** argv) {
//    string test_file = "../../tests/test_parser1";
//    string test_file = "../../tests/test_arithm_expr1";
//    string test_file = "../../tests/test_parser2";
//    string test_file = "../../tests/test_lexer1";
//    string test_file = "../../tests/test_eval1";

//    TestLexer(test_file, false);
//    TestParser(test_file);
//    TestEvaluation(test_file);

    if(argc != 2) {
        cout << "error: incorrect arguments" << endl;
        return 0;
    }
    string input_file_path = argv[1];
    Lexer lexer;
    int res = lexer.Tokenize(input_file_path);
    if(res < 0) {
        cout << "error: can't open file" << endl;
        return 0;
    }
    Parser parser(lexer.tokens());
    Error error;
    Program program(parser.Parse(error));
    if(error.IsOccured()) {
        cout << error.GetErrorMessage() << endl;
        return 0;
    }
    Evaluator eva;
    program.accept(eva);
    if(program.RuntimeErrorIsOccured()) {
        cout << program.GetErrorMessage() << endl;
        return 0;
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
    if(error.IsOccured()) {
        cout << error.GetErrorMessage() << endl;
        return;
    }
    Evaluator eva;
    program.accept(eva);
    if(program.RuntimeErrorIsOccured()) {
        cout << program.GetErrorMessage() << endl;
        return;
    }
    cout << endl << "Evaluation test successfully completed" << endl;
}
