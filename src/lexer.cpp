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
static const char OCTOTH = '#';
static const char OPEN_BR = '(';
static const char CLOSE_BR = ')';
static const char UNDERSC = '_';

//This function returns 0 if everything is fine.
//If there is some lexical error in input file returns line number where the error occures
//(line numbers begin with 1)
//If there is a problem with file opening returns -1
size_t Lexer::Tokenize(string const& file_name) {
    input_.close();
    input_.open(file_name.c_str(), std::ios_base::in);
    if(!input_.is_open()) {
        return -1;
    }
    while(true) {
        ssize_t res = TokenizeNextWord();
        if(res == -1) {
            return 0;
        }
        if(res > 0) {
            return res;
        }
    }
}

//This function returns -1 in case of EOF, 0 - if everything is fine.
//If next word contains lexical errors returns number of current line in input file
ssize_t Lexer::TokenizeNextWord() {
    string current_word = ReadWord();
    if(!ParseWord(current_word)) {
        return current_line_;
    }
    if(input_.eof()) {
        return -1;
    }
    return 0;
}

string Lexer::ReadWord() {
    int symb;
    string word;
    while((symb = input_.get()) != ' ' && symb != '\t' && symb != EOF && symb != '\n') {
        word += static_cast<char>(symb);
    }
    if(symb == EOF) {
        ++current_line_;
    }
    return word + static_cast<char>(symb);
}

bool Lexer::ParseWord(string const& word) {
    string token_val;
    for(size_t i = 0; i != word.size() - 1; ++i) {
        TokenType type = DefineType(word[i]);
        if(type == UNKNOWN) {
            return false;
        }
        //if current symbol is not a part of ID, KEYWORD or NUMBER tokens
        if(type != ID) {
            if(!token_val.empty()) {
                TokenType prev_token_type = DefineCompositeTokenType(token_val);
                if(prev_token_type == UNKNOWN) {
                    return false;
                }
                tokens_.push_back(Token(prev_token_type, token_val));
                token_val.clear();
            }
            //if current token is comment token begining
            if(type == COMMENT) {
                string string_rest_part;
                if(word[word.size() - 1] == ' ' || word[word.size() - 1] == '\t') {
                    std::getline(input_, string_rest_part);
                    ++current_line_;
                }
                tokens_.push_back(Token(type, word.substr(i, word.size()) + string_rest_part));
                return true;
            }
            //if current token is 2 symbols comparison token
            else if(type == COMPARISON_CHAR && (i + 1) != word.size() && word[i + 1] == ASSIGN) {
                tokens_.push_back(Token(type, (string() + word[i]) + word[i + 1])); // conversation from char to string
                ++i;
            }
            //if current token is one symbol token
            else {
                tokens_.push_back(Token(type, string() + word[i]));
            }
        }
        else {
            token_val += word[i];
        }
    }
    if(!token_val.empty()) {
        TokenType token_type = DefineCompositeTokenType(token_val);
        if(token_type == UNKNOWN) {
            return false;
        }
        tokens_.push_back(Token(token_type, token_val));
        token_val.clear();
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
    else if(symbol == OCTOTH) {
        return COMMENT;
    }
    return UNKNOWN;
}

TokenType Lexer::DefineCompositeTokenType(string const& token_value) {
    if(isalpha(token_value[0])) {
        bool token_is_keyword = false;
        for(size_t i = 0; i != KEYWORDS_NUMBER; ++i) {
            if(token_value.compare(KEYWORDS[i])) {
                token_is_keyword = true;
                break;
            }
        }
        if(token_is_keyword) {
            return KEYWORD;
        }
        return ID;
    }
    bool token_is_number = true;
    for(size_t i = 1; i != token_value.size(); ++i) {
        if(!isdigit(token_value[i])) {
            token_is_number = false;
            break;
        }
    }
    if(token_is_number) {
        return NUMBER;
    }
    return UNKNOWN;
}
