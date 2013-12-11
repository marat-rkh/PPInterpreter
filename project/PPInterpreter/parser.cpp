#include "parser.h"
#include "lexer.h"

size_t Parser::Parse() {
    while(!tokens_.End()) {
        if(!ParseStmt()) {
            return current_line_;
        }
    }
    return 0;
}

bool Parser::ParseStmt() {
    if(tokens_.CompareTypeWithRollback(NEWLINE)) {
        ++current_line_;
        return true;
    }
    ParsingResult func_res = ParseFuncDecl();
    if(func_res == CORRECT) {
        return true;
    }
    ParsingResult instr_res = ParseInstruction();
    if(instr_res == CORRECT) {
        return true;
    }
    return false;
}

ParsingResult Parser::ParseFuncDecl() {
    if(!tokens_.CompareValueWithRollback(KEYWORDS[0])) {
        return NOT_MATCHED;
    }
    if(!tokens_.NextTokenTypeEqualsTo(ID) ||
       !tokens_.NextTokenTypeEqualsTo(OPEN_BRACE) ||
       (tokens_.CompareTypeWithRollback(ID) && !CheckFuncParams()) ||
       !tokens_.NextTokenTypeEqualsTo(CLOSE_BRACE) ||
       !tokens_.NextTokenTypeEqualsTo(COLUMN) ||
       !tokens_.NextTokenTypeEqualsTo(NEWLINE))
    {
        return INCORRECT;
    }
    ++current_line_;
    bool body_is_ok = CheckFuncBody();
    if(!body_is_ok) {
        return INCORRECT;
    }
    if(!tokens_.NextTokenTypeEqualsTo(NEWLINE)) {
        return INCORRECT;
    }
    ++current_line_;
    return CORRECT;
}

bool Parser::CheckFuncParams() {
    if(!tokens_.CompareTypeWithRollback(COMMA)) {
        return true;
    }
    else if(!tokens_.NextTokenTypeEqualsTo(ID)) {
        return false;
    }
    return CheckFuncParams();
}

bool Parser::CheckFuncBody() {
    ParsingResult instr_res = ParseInstruction();
    if(instr_res == INCORRECT) {
        return tokens_.NextTokenValueEqualsTo(KEYWORDS[1]);
    }
    return CheckFuncBody();
}

ParsingResult Parser::ParseInstruction() {
    if(!tokens_.CompareTypeWithRollback(NEWLINE)) {
        return INCORRECT;
    }
    ++current_line_;
    return CORRECT;
}
