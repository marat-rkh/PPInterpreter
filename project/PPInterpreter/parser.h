#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "lexer.h"

using std::vector;

class Parser {
  public:
    Parser(vector<Token> const& tokens):
        tokens_(tokens),
        current_line_(1),
        current_pos_(0)
    {}
    size_t Parse();

  private:
    bool ParseStmt();

    ssize_t ParseFuncDecl();
    bool CheckFuncParams();
    bool CheckFuncBody();

    ssize_t ParseInstruction();

    vector<Token> tokens_;
    size_t current_line_;
    size_t current_pos_;
};

#endif // PARSER_H
