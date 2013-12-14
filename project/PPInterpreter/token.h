#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {ID,
                KEYWORD,
                NUMBER,
                PLUS_OP,
                MINUS_OP,
                MUL_OP,
                DIV_OP,
                COMPARISON_CHAR,
                ASSIGN_OP,
                COLUMN,
                COMMA,
                OPEN_BRACE,
                CLOSE_BRACE,
                COMMENT,
                WHITESPACE,
                NEWLINE,
                UNKNOWN};

class Token {
  public:
    Token(TokenType type, std::string val): type_(type), value_(val) {}
    TokenType type_;
    std::string value_;
};

#endif // TOKEN_H
