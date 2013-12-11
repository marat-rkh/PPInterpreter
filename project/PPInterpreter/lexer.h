#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream>

#include "token.h"

#define DISABLE_COPY_AND_ASSIGN(TypeName) \
    TypeName(TypeName const&); \
    void operator=(TypeName const&)

using std::string;
using std::fstream;
using std::vector;

static const string KEYWORDS[] = {"def", "end", "if", "while", "return",};
static const size_t KEYWORDS_NUMBER = 5;

class Lexer {
  public:
    Lexer(): current_line_(1) {}
    int Tokenize(string const& file_name);
    vector<Token> tokens() { return tokens_; }

  private:
    DISABLE_COPY_AND_ASSIGN(Lexer);

    bool TryParseLine(string const& line);
    TokenType DefineType(char symbol);
    bool TryParseCompositeToken(string const& token_value);
    TokenType DefineCompositeTokenType(string const& token_value);
    bool TokenIsKeyword(string token_value);
    bool TokenIsNumber(string token_value);

    fstream input_;
    vector<Token> tokens_;
    size_t current_line_;
};

#endif // LEXER_H
