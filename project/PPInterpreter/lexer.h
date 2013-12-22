#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream>

#include "defines.h"
#include "error.h"

using std::string;
using std::fstream;
using std::vector;

enum TokenType {ID,
                KEYWORD,
                NUMBER,
                PLUS_OP,
                MINUS_OP,
                MUL_OP,
                DIV_OP,
                COMPARISON_OP,
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

static const string KEYWORDS[] = {"def", "end", "if", "while", "return", "print", "read"};
static const size_t KEYWORDS_NUMBER = 7;

class Lexer {
public:
    Lexer(): current_line_(1), lexing_error_(false), fopen_error_(false) {}
    void Tokenize(string const& file_name);
    vector<Token> tokens() {
        return tokens_;
    }
    bool IsErrorOccured() {
        return lexing_error_ || fopen_error_;
    }
    std::string GetErrorMessage() {
        if(lexing_error_) {
            return "line " + std::to_string(current_line_) + ": syntax error";
        }
        else if(fopen_error_) {
            return "can't open file";
        }
        return "no errors";
    }

private:
    DISABLE_COPY_AND_ASSIGN(Lexer);

    bool TryParseLine(string const& line);
    TokenType ParseSymbol(char symbol);
    bool TryParseToken(string const& token_value);
    TokenType DetermineTokenType(string const& token_value);

    fstream input_;
    vector<Token> tokens_;
    size_t current_line_;
    bool lexing_error_;
    bool fopen_error_;
};

#endif // LEXER_H
