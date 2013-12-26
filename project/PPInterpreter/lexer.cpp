#include "lexer.h"

#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>

using std::string;
using std::vector;
using std::fstream;

static const std::map<char, TokenType> tok_types = {
    {'_', ID},
    {'+', PLUS_OP},
    {'-', MINUS_OP},
    {'*', MUL_OP},
    {'/', DIV_OP},
    {'>', COMPARISON_OP},
    {'<', COMPARISON_OP},
    {'!', COMPARISON_OP},
    {'=', COMPARISON_OP},
    {':', COLUMN},
    {',', COMMA},
    {'(', OPEN_BRACE},
    {')', CLOSE_BRACE},
    {'#', COMMENT},
    {' ', WHITESPACE},
    {'\t', WHITESPACE},
};

static const char ASSIGN = '=';
static const char NLINE = '\n';

void Lexer::Tokenize(string const& file_name) {
    input_.close();
    tokens_.empty();
    current_line_ = 1;
    error_.empty();
    input_.open(file_name.c_str(), std::ios_base::in);
    if(!input_.is_open()) {
        error_ = "fopen_error";
        return;
    }
    while(!input_.eof()) {
        string line;
        std::getline(input_, line);
        if(!TryParseLine(line)) {
            error_ = "syntax_error";
            return;
        }
        tokens_.push_back(Token(NEWLINE, string() + NLINE));
        ++current_line_;
    }
}

bool Lexer::TryParseLine(string const& line) {
    string token_val;
    for(size_t i = 0; i != line.size(); ++i) {
        TokenType type = ParseSymbol(line[i]);
        if(type == UNKNOWN) {
            return false;
        }
        if(type == ID) {
            token_val += line[i];
            continue;
        }
        //if current symbol is not a part of ID, KEYWORD or NUMBER tokens
        if(!TryParseToken(token_val)) {
            return false;
        }
        token_val.clear();
        switch(type) {
        case WHITESPACE:
            continue;
        case COMMENT:
            return true;
        case COMPARISON_OP:
            if(i + 1 != line.size() && line[i + 1] == ASSIGN) {
                tokens_.push_back(Token(type, (string() + line[i]) + line[i + 1]));
                ++i;
                break;
            }
        default:
            if(line[i] == ASSIGN) { type = ASSIGN_OP; }
            tokens_.push_back(Token(type, string() + line[i]));
        }
    }
    return TryParseToken(token_val);
}

TokenType Lexer::ParseSymbol(char symbol) {
    if(isdigit(symbol) || isalpha(symbol)) {
        return ID;
    }
    std::map<char, TokenType>::const_iterator it = tok_types.find(symbol);
    return it == tok_types.end() ? UNKNOWN : it->second;
}

bool Lexer::TryParseToken(string const& token_value) {
    if(!token_value.empty()) {
        TokenType token_type = DetermineTokenType(token_value);
        if(token_type == UNKNOWN) {
            return false;
        }
        tokens_.push_back(Token(token_type, token_value));
    }
    return true;
}

TokenType Lexer::DetermineTokenType(string const& token_value) {
    if(isalpha(token_value[0])) {
        if(std::find(KEYWORDS.begin(), KEYWORDS.end(), token_value) != KEYWORDS.end()) {
            return KEYWORD;
        }
        return ID;
    }
    if(std::all_of(token_value.begin(), token_value.end(), isdigit)) {
        return NUMBER;
    }
    return UNKNOWN;
}
