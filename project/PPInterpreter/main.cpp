#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"
#include "parser.h"

#include "ast.h"
#include "evaluator.h"
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
    string test_file = "../../tests/test_eval1";

    TestLexer(test_file, false);
    TestParser(test_file);
    TestEvaluation(test_file);

//    if(argc != 2) {
//        cout << "error: incorrect arguments" << endl;
//        return 1;
//    }
//    string input_file_path = argv[1];
//    Lexer lexer;
//    lexer.Tokenize(input_file_path);
//    if(lexer.IsErrorOccured()) {
//        cout << lexer.GetErrorMessage() << endl;
//        return 1;
//    }
//    std::vector<Token> tokens = lexer.tokens();
//    Parser parser;
//    Program program(parser.Parse(tokens));
//    if(parser.error_occured_) {
//        cout << "line " << parser.current_line_ << ": syntax error" << endl;
//        return 1;
//    }
//    Evaluator eva;
//    program.accept(eva);
//    if(program.RuntimeErrorIsOccured()) {
//        cout << program.GetErrorMessage() << endl;
//        return 1;
//    }
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
    lexer.Tokenize(test_file);
    if(lexer.IsErrorOccured()) {
        cout << lexer.GetErrorMessage() << endl;
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
    Parser parser;
    std::vector<Token> tokens = lexer.tokens();
    parser.Parse(tokens);
    if(parser.error_occured_) {
        cout << "line " << parser.current_line_ << ": syntax error" << endl;
        return;
    }
    cout << "Parse test successfully completed" << endl;
}

void TestEvaluation(std::string test_file) {
    Lexer lexer;
    lexer.Tokenize(test_file);
    Parser parser;
    std::vector<Token> tokens = lexer.tokens();
    Program program(parser.Parse(tokens));
    Evaluator eva;
    program.accept(eva);
    if(program.RuntimeErrorIsOccured()) {
        cout << program.GetErrorMessage() << endl;
        return;
    }
    cout << endl << "Evaluation test successfully completed" << endl;
}
