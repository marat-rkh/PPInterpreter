#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream>

#include "token.h"
#include "defines.h"
#include "error.h"

using std::string;
using std::fstream;
using std::vector;

static const string KEYWORDS[] = {"def", "end", "if", "while", "return", "print", "read"};
static const size_t KEYWORDS_NUMBER = 7;

class Lexer {
public:
    Lexer(): current_line_(1) {}
    void Tokenize(string const& file_name, Error& error);
    vector<Token> tokens() { return tokens_; }

private:
    DISABLE_COPY_AND_ASSIGN(Lexer);

    bool TryParseLine(string const& line);
    TokenType ParseSymbol(char symbol);
    bool TryParseToken(string const& token_value);
    TokenType DetermineTokenType(string const& token_value);

    fstream input_;
    vector<Token> tokens_;
    size_t current_line_;
};

#endif // LEXER_H
