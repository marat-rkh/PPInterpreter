#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::fstream;
using std::vector;

enum TokenType {ID,
                KEYWORD,
                NUMBER,
                ARITHMETIC_OP,
                COMPARISON_CHAR,
                ASSIGN_OP,
                COLUMN,
                COMMA,
                OPEN_BRACE,
                CLOSE_BRACE,
                COMMENT,
                UNKNOWN};

static const string KEYWORDS[] = {"def", "end", "if", "while", "return",};
static const size_t KEYWORDS_NUMBER = 5;

class Token {
  public:
    Token() {}
    Token(TokenType type, string val): type_(type), value_(val) {}
    TokenType type_;
    string value_;
};

class Lexer {
  public:
    Lexer(): current_line_(1) {}
    size_t Tokenize(string const& file_name);
    vector<Token> tokens() { return tokens_; }

  private:
    ssize_t TokenizeNextWord();
    string ReadWord();
    bool ParseWord(string const& word);
    TokenType DefineType(char symbol);
    TokenType DefineCompositeTokenType(string const& token_value);

    fstream input_;
    vector<Token> tokens_;
    size_t current_line_;
};

#endif // LEXER_H
