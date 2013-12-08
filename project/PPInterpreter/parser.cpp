#include "parser.h"

size_t Parser::Parse() {
    while(current_pos_ != tokens_.size()) {
        if(!ParseStmt()) {
            return current_line_;
        }
    }
    return 0;
}

bool Parser::ParseStmt() {
    if(tokens_[current_pos_].type_ == NEWLINE) {
        ++current_pos_;
        ++current_line_;
        return true;
    }
    ssize_t func_res = ParseFuncDecl();
    if(func_res > 0) {
        return false;
    }
    ssize_t instr_res = ParseInstruction();
    if(instr_res > 0) {
        return false;
    }
    if(func_res == -1 && instr_res == -1) {
        return false;
    }
    return true;
}

ssize_t Parser::ParseFuncDecl() {
    if(tokens_[current_pos_].value_.compare(KEYWORDS[0])) {
        return -1;
    }
    if(tokens_[++current_pos_].type_ != ID ||
       tokens_[++current_pos_].type_ != OPEN_BRACE ||
       (tokens_[++current_pos_].type_ == ID && !CheckFuncParams()) ||
       tokens_[++current_pos_].type_ != CLOSE_BRACE ||
       tokens_[++current_pos_].type_ != COLUMN ||
       tokens_[++current_pos_].type_ != NEWLINE)
    {
        return 1;
    }
    ++current_line_;
    bool body_is_ok = CheckFuncBody();
    if(!body_is_ok) {
        return 1;
    }
    if(tokens_[++current_pos_].value_.compare(KEYWORDS[1]) ||
       tokens_[++current_pos_].type_ != NEWLINE)
    {
        return 1;
    }
    return 0;
}

bool Parser::CheckFuncParams() {
    if(tokens_[++current_pos_].type_ != COMMA) {
        --current_pos_;
        return true;
    }
    else if(tokens_[++current_pos_].type_ != ID) {
        return false;
    }
    return CheckFuncParams();
}

bool Parser::CheckFuncBody() {
    ssize_t instr_res = ParseInstruction();
    if(instr_res > 0) {
        return false;
    }
    if(instr_res == -1) {
        return true;
    }
    return CheckFuncBody();
}

ssize_t Parser::ParseInstruction() {
    if(tokens_[++current_pos_].type_ == NEWLINE ||
       (tokens_[current_pos_].type_ == COMMENT && tokens_[++current_pos_].type_ == NEWLINE)) {
        ++current_line_;
        return 0;
    }
    else if(tokens_[--current_pos_].type_ == COMMENT){
        return 1;
    }
    return -1;
}
