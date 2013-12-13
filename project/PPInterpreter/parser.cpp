#include "parser.h"
#include "lexer.h"

size_t Parser::Parse() {
    while(!tokens_.End()) {
        ParsingResult stmt_res = ParseStmt();
        if(stmt_res == INCORRECT || !tokens_.NextTokenTypeEqualsTo(NEWLINE)) { return current_line_; }
        ++current_line_;
    }
    return 0;
}

ParsingResult Parser::ParseStmt() {
    ParsingResult func_res = ParseFuncDecl();
    if(func_res != NOT_MATCHED) {
        return func_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult instr_res = ParseInstruction();
    if(instr_res != NOT_MATCHED) {
        return instr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseFuncDecl() {
    if(!tokens_.CompareValueWithRollback(KEYWORDS[0])) {
        return NOT_MATCHED;
    }
    ParsingResult func_call_res = ParseFuncCall();
    if(func_call_res != CORRECT) { return INCORRECT; }
    if(!CheckBlock()) { return INCORRECT; }
    return CORRECT;
}

ParsingResult Parser::ParseFuncCall() {
    tokens_.FixPosition();
    if(!tokens_.CompareTypeWithRollback(ID)) { return NOT_MATCHED; }
    if(!tokens_.CompareTypeWithRollback(OPEN_BRACE)) {
        tokens_.RollbackToFixedPosition();
        return NOT_MATCHED;
    }
    if(tokens_.CompareTypeWithRollback(ID) && !CheckFuncParams()) { return INCORRECT; }
    if(!tokens_.NextTokenTypeEqualsTo(CLOSE_BRACE)) { return INCORRECT; }
    return CORRECT;
}

bool Parser::CheckFuncParams() {
    if(!tokens_.CompareTypeWithRollback(COMMA)) { return true; }
    else if(!tokens_.NextTokenTypeEqualsTo(ID)) { return false; }
    return CheckFuncParams();
}

bool Parser::CheckBlock() {
    if(!tokens_.NextTokenTypeEqualsTo(COLUMN) ||
       !tokens_.NextTokenTypeEqualsTo(NEWLINE))
    {
        return false;
    }
    ++current_line_;
    return CheckBlockBody();
}

bool Parser::CheckBlockBody() {
    ParsingResult instr_res = ParseInstruction();
    if(instr_res == INCORRECT) { return false; }
    if(!tokens_.CompareTypeWithRollback(NEWLINE)) {
       if(instr_res == CORRECT) { return false; }
       return tokens_.NextTokenValueEqualsTo(KEYWORDS[1]);
    }
    ++current_line_;
    return CheckBlockBody();
}

ParsingResult Parser::ParseInstruction() {
    ParsingResult io_res = ParseIOInstr();
    if(io_res != NOT_MATCHED) {
        return io_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult contr_flow_res = ParseControlFlowInstr();
    if(contr_flow_res != NOT_MATCHED) {
        return contr_flow_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult assign_res = ParseAssignment();
    if(assign_res != NOT_MATCHED) {
        return assign_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult func_call_res = ParseFuncCall();
    if(func_call_res != NOT_MATCHED) {
        return func_call_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult return_expr_res = ParseReturnExpr();
    if(return_expr_res != NOT_MATCHED) {
        return return_expr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseIOInstr() {
    if(tokens_.CompareValueWithRollback(KEYWORDS[6])) {
        return tokens_.CompareTypeWithRollback(ID) ? CORRECT : INCORRECT;
    }
    if(tokens_.CompareValueWithRollback(KEYWORDS[5])) {
        return ParseExpr() == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseControlFlowInstr() {
    if(!tokens_.CompareValueWithRollback(KEYWORDS[2]) &&
       !tokens_.CompareValueWithRollback(KEYWORDS[3]))
    {
        return NOT_MATCHED;
    }
    ParsingResult expr_res = ParseExpr();
    if(expr_res == INCORRECT || expr_res == NOT_MATCHED) { return INCORRECT; }
    if(!tokens_.NextTokenTypeEqualsTo(COMPARISON_CHAR)) { return INCORRECT; }
    expr_res = ParseExpr();
    if(expr_res == INCORRECT ||
       expr_res == NOT_MATCHED ||
       !CheckBlock())
    {
        return INCORRECT;
    }
    return CORRECT;
}

ParsingResult Parser::ParseAssignment() {
    tokens_.FixPosition();
    if(!tokens_.CompareTypeWithRollback(ID)) { return NOT_MATCHED; }
    if(!tokens_.CompareTypeWithRollback(ASSIGN_OP)) {
        tokens_.RollbackToFixedPosition();
        return NOT_MATCHED;
    }
    ParsingResult expr_res = ParseExpr();
    return expr_res == CORRECT ? CORRECT : INCORRECT;
}

ParsingResult Parser::ParseReturnExpr() {
    if(!tokens_.CompareValueWithRollback(KEYWORDS[4])) { return NOT_MATCHED; }
    ParsingResult expr_res = ParseExpr();
    if(expr_res != NOT_MATCHED) {
        return expr_res == CORRECT ? CORRECT : INCORRECT;
    }
    tokens_.FixPosition();
    if(!tokens_.NextTokenTypeEqualsTo(NEWLINE)) {
        return INCORRECT;
    }
    tokens_.RollbackToFixedPosition();
    return CORRECT;
}

ParsingResult Parser::ParseExpr() {
    ParsingResult func_call_res = ParseFuncCall();
    if(func_call_res != NOT_MATCHED) {
        return func_call_res == CORRECT ? CORRECT : INCORRECT;
    }
    if(tokens_.CompareTypeWithRollback(ID)) {
        return CORRECT;
    }
    //check ArithmExpr
    return NOT_MATCHED;
}
