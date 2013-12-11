#include "lexer.h"

#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cctype>

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

//This function returns 0 if everything is fine.
//If there is some lexical error in input file returns line number where the error occures
//(line numbers begin with 1)
//If there is a problem with file opening returns -1
int Lexer::Tokenize(string const& file_name) {
    input_.close();
    input_.open(file_name.c_str(), std::ios_base::in);
    if(!input_.is_open()) {
        return -1;
    }
    while(!input_.eof()) {
        string line;
        std::getline(input_, line);
        if(!TryParseLine(line)) {
            return current_line_;
        }
        tokens_.push_back(Token(NEWLINE, string() + NLINE));
        ++current_line_;
    }
    return 0;
}

bool Lexer::TryParseLine(string const& line) {
    string token_val;
    for(size_t i = 0; i != line.size(); ++i) {
        TokenType type = DefineType(line[i]);
        if(type == UNKNOWN) {
            return false;
        }
        if(type == ID) {
            token_val += line[i];
        }
        //if current symbol is not a part of ID, KEYWORD or NUMBER tokens
        else {
            if(!TryParseCompositeToken(token_val)) { return false; }
            token_val.clear();
            if(type == WHITESPACE) { continue; }
            //if current token is comment token begining
            if(type == COMMENT) { return true; }
            //if current token is 2 symbols comparison character
            else if(type == COMPARISON_CHAR && (i + 1) != line.size() && line[i + 1] == ASSIGN) {
                tokens_.push_back(Token(type, (string() + line[i]) + line[i + 1])); // conversation from char to string
                ++i;
            }
            //if current token is one symbol token
            else {
                tokens_.push_back(Token(type, string() + line[i]));
            }
        }
    }
    if(!TryParseCompositeToken(token_val)) {
        return false;
    }
    return true;
}

TokenType Lexer::DefineType(char symbol) {
    if(symbol == PLUS || symbol == MINUS || symbol == MUL || symbol == DIV) {
        return ARITHMETIC_OP;
    }
    else if(symbol == GR || symbol == LESS || symbol == NOT || symbol == ASSIGN) {
        return COMPARISON_CHAR;
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
    else if(isdigit(symbol) || isalpha(symbol) || symbol == UNDERSC) {
        return ID;
    }
    else if(symbol == SHARP) {
        return COMMENT;
    }
    else if(symbol == TAB || symbol == SPACE) {
        return WHITESPACE;
    }
    return UNKNOWN;
}

bool Lexer::TryParseCompositeToken(string const& token_value) {
    if(!token_value.empty()) {
        TokenType token_type = DefineCompositeTokenType(token_value);
        if(token_type == UNKNOWN) {
            return false;
        }
        tokens_.push_back(Token(token_type, token_value));
    }
    return true;
}

TokenType Lexer::DefineCompositeTokenType(string const& token_value) {
    if(isalpha(token_value[0])) {
        if(TokenIsKeyword(token_value)) {
            return KEYWORD;
        }
        return ID;
    }
    if(TokenIsNumber(token_value)) {
        return NUMBER;
    }
    return UNKNOWN;
}

bool Lexer::TokenIsKeyword(string token_value) {
    bool token_is_keyword = false;
    for(size_t i = 0; i != KEYWORDS_NUMBER; ++i) {
        if(token_value == KEYWORDS[i]) {
            token_is_keyword = true;
            break;
        }
    }
    return token_is_keyword;
}

bool Lexer::TokenIsNumber(string token_value) {
    bool token_is_number = true;
    for(size_t i = 0; i != token_value.size(); ++i) {
        if(!isdigit(token_value[i])) {
            token_is_number = false;
            break;
        }
    }
    return token_is_number;
}
