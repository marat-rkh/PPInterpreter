#include "lexer.h"

#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <algorithm>

using std::string;
using std::vector;
using std::fstream;

//arithmetic operators
static const char PLUS = '+';
static const char MINUS = '-';
static const char MUL = '*';
static const char DIV = '/';
//comparison characters parts
static const char GR = '>';
static const char LESS = '<';
static const char NOT = '!';
//other symbols
static const char ASSIGN = '=';
static const char COL = ':';
static const char COM = ',';
static const char SHARP = '#';
static const char OPEN_BR = '(';
static const char CLOSE_BR = ')';
static const char UNDERSC = '_';
static const char SPACE = ' ';
static const char TAB = '\t';
static const char NLINE = '\n';

void Lexer::Tokenize(string const& file_name) {
    input_.close();
    input_.open(file_name.c_str(), std::ios_base::in);
    if(!input_.is_open()) {
        fopen_error_ = true;
        return;
    }
    while(!input_.eof()) {
        string line;
        std::getline(input_, line);
        if(!TryParseLine(line)) {
            lexing_error_ = true;
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
        if(type == UNKNOWN) { return false; }
        if(type == ID) {
            token_val += line[i];
            continue;
        }
        //if current symbol is not a part of ID, KEYWORD or NUMBER tokens
        if(!TryParseToken(token_val)) { return false; }
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
    if(!TryParseToken(token_val)) {
        return false;
    }
    return true;
}

TokenType Lexer::ParseSymbol(char symbol) {
    if(isdigit(symbol) || isalpha(symbol) || symbol == UNDERSC) {
        return ID;
    }
    else if(symbol == PLUS) {
        return PLUS_OP;
    }
    else if(symbol == MINUS) {
        return MINUS_OP;
    }
    else if(symbol == MUL) {
        return MUL_OP;
    }
    else if(symbol == DIV) {
        return DIV_OP;
    }
    else if(symbol == GR || symbol == LESS || symbol == NOT || symbol == ASSIGN) {
        return COMPARISON_OP;
    }
    else if(symbol == COL) {
        return COLUMN;
    }
    else if(symbol == COM) {
        return COMMA;
    }
    else if(symbol == OPEN_BR) {
        return OPEN_BRACE;
    }
    else if(symbol == CLOSE_BR) {
        return CLOSE_BRACE;
    }
    else if(symbol == SHARP) {
        return COMMENT;
    }
    else if(symbol == TAB || symbol == SPACE) {
        return WHITESPACE;
    }
    return UNKNOWN;
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
        if(std::find(KEYWORDS, KEYWORDS + KEYWORDS_NUMBER, token_value) != KEYWORDS + KEYWORDS_NUMBER) {
            return KEYWORD;
        }
        return ID;
    }
    if(std::all_of(token_value.begin(), token_value.end(), isdigit)) {
        return NUMBER;
    }
    return UNKNOWN;
}
