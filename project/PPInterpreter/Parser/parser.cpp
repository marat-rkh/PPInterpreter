#include "parser.h"
#include "lexer.h"

#include "Creators/funccreator.h"

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
    InstructionBlock body;      //!!!!!!!!!!!!!!!------------------!!!!!!!!!!!!!!!!!!!!!!
    ParsingResult instr_res = ParseInstruction(body);
    if(instr_res != NOT_MATCHED) {
        return instr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseFuncDecl() {
    if(!tokens_.CompareValueWithRollback(KEYWORDS[0])) {
        return NOT_MATCHED;
    }
    FuncCreator func_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncDeclParams, func_creator);
    if(func_res != CORRECT) { return INCORRECT; }
    InstructionBlock body;
    if(!CheckBlock(body)) { return INCORRECT; }
    func_creator.CreateWithBody(body);
    return CORRECT;
}

template<class T>
ParsingResult Parser::ParseFuncHeader(bool (Parser::*ParamsChecker)(T&), T& creator) {
    tokens_.FixPosition();
    if(!tokens_.CompareTypeWithRollback(ID)) { return NOT_MATCHED; }
    creator.SetID(tokens_.GetCurrentTokenValue());
    if(!tokens_.CompareTypeWithRollback(OPEN_BRACE)) {
        tokens_.RollbackToFixedPosition();
        return NOT_MATCHED;
    }
    if(!(this->*ParamsChecker)(creator) ||
       !tokens_.NextTokenTypeEqualsTo(CLOSE_BRACE)) { return INCORRECT; }
    return CORRECT;
}

bool Parser::CheckFuncDeclParams(FuncCreator& creator) {
    if(!tokens_.CompareTypeWithRollback(ID)) { return true; }
    creator.AddParam(tokens_.GetCurrentTokenValue());
    return CheckFuncDeclParamsLoop(creator) ? true : false;
}

bool Parser::CheckFuncDeclParamsLoop(FuncCreator& creator) {
    if(!tokens_.CompareTypeWithRollback(COMMA)) { return true; }
    else if(!tokens_.NextTokenTypeEqualsTo(ID)) { return false; }
    creator.AddParam(tokens_.GetCurrentTokenValue());
    return CheckFuncDeclParamsLoop(creator);
}

bool Parser::CheckFuncCallParams(FuncCallCreator& creator) {
    Expr expr; // !!!!!!!!!!!!!!!!!!!!!--------------create expression-------------------!!!!!!!!!!!!!!!
    ParsingResult expr_res = ParseExpr();
    if(expr_res != CORRECT) {
        return expr_res == NOT_MATCHED;
    }
    creator.AddParam(expr);
    return CheckFuncCallParamsLoop(creator) ? true : false;
}

bool Parser::CheckFuncCallParamsLoop(FuncCallCreator& creator) {
    if(!tokens_.CompareTypeWithRollback(COMMA)) { return true; }
    else {
        Expr expr; // !!!!!!!!!!!!!!!!!!!!!--------------create expression-------------------!!!!!!!!!!!!!!!
        ParsingResult expr_res = ParseExpr();
        if(expr_res != CORRECT) { return false; }
        creator.AddParam(expr);
    }
    return CheckFuncCallParamsLoop(creator);
}

bool Parser::CheckBlock(InstructionBlock& body) {
    if(!tokens_.NextTokenTypeEqualsTo(COLUMN) ||
       !tokens_.NextTokenTypeEqualsTo(NEWLINE))
    {
        return false;
    }
    ++current_line_;
    return CheckBlockBody(body);
}

bool Parser::CheckBlockBody(InstructionBlock& body) {
    ParsingResult instr_res = ParseInstruction(body);
    if(instr_res == INCORRECT) { return false; }
    if(!tokens_.CompareTypeWithRollback(NEWLINE)) {
       if(instr_res == CORRECT) { return false; }
       return tokens_.NextTokenValueEqualsTo(KEYWORDS[1]);
    }
    ++current_line_;
    return CheckBlockBody(body);
}

ParsingResult Parser::ParseInstruction(InstructionBlock& body) {
    ParsingResult io_res = ParseIOInstr(body);
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
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncCallParams, func_call_creator);
    if(func_res != NOT_MATCHED) {
        return func_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult return_expr_res = ParseReturnExpr();
    if(return_expr_res != NOT_MATCHED) {
        return return_expr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseIOInstr(InstructionBlock& body) {

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
    InstructionBlock tmp_bl;
    if(expr_res == INCORRECT ||
       expr_res == NOT_MATCHED ||
       !CheckBlock(tmp_bl))
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
    ParsingResult term_res = ParseTerm();
    if(term_res != CORRECT) {
        return term_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
    }
    return CheckExprLoop() ? CORRECT : INCORRECT;
}

bool Parser::CheckExprLoop() {
    if(!tokens_.CompareTypeWithRollback(PLUS_OP) &&
       !tokens_.CompareTypeWithRollback(MINUS_OP))
    {
        return true;
    }
    ParsingResult term_res = ParseTerm();
    if(term_res != CORRECT) { return false; }
    return CheckExprLoop();
}

ParsingResult Parser::ParseTerm() {
    ParsingResult fact_res = ParseFactor();
    if(fact_res != CORRECT) {
        return fact_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
    }
    return CheckTermLoop() ? CORRECT : INCORRECT;
}

bool Parser::CheckTermLoop() {
    if(!tokens_.CompareTypeWithRollback(MUL_OP) &&
       !tokens_.CompareTypeWithRollback(DIV_OP))
    {
        return true;
    }
    ParsingResult fact_res = ParseFactor();
    if(fact_res != CORRECT) { return false; }
    return CheckTermLoop();
}

ParsingResult Parser::ParseFactor() {
    if(tokens_.CompareTypeWithRollback(MINUS_OP)) { /*code to add minus to number*/ }
    if(tokens_.CompareTypeWithRollback(PLUS_OP)) { /*code to add plus to number*/ }
    if(tokens_.CompareTypeWithRollback(NUMBER)) { return CORRECT; }
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncCallParams, func_call_creator);
    if(func_res != NOT_MATCHED) {
        return func_res == CORRECT ? CORRECT : INCORRECT;
    }
    if(tokens_.CompareTypeWithRollback(ID)) { return CORRECT; }
    if(!tokens_.CompareTypeWithRollback(OPEN_BRACE)) { return NOT_MATCHED; }
    ParsingResult expr_res = ParseExpr();
    if(expr_res != CORRECT) {
        return INCORRECT;
    }
    return tokens_.NextTokenTypeEqualsTo(CLOSE_BRACE) ? CORRECT : INCORRECT;
}

//ParsingResult Parser::ParseArithmExpr(int& i) {
//    ParsingResult term_res = ParseTerm(i);
//    if(term_res != CORRECT) {
//        return term_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
//    }
//    return CheckArithmExprLoop(i) ? CORRECT : INCORRECT;
//}

//bool Parser::CheckArithmExprLoop(int& i) {
//    if(!tokens_.CompareTypeWithRollback(PLUS_OP) &&
//       !tokens_.CompareTypeWithRollback(MINUS_OP))
//    {
//        return true;
//    }
//    int res = 0;
//    ParsingResult term_res = ParseTerm(res);
//    if(term_res != CORRECT) { return false; }
//    i += res;
//    return CheckArithmExprLoop(i);
//}

//ParsingResult Parser::ParseTerm(int& i) {
//    ParsingResult fact_res = ParseFactor(i);
//    if(fact_res != CORRECT) {
//        return fact_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
//    }
//    return CheckTermLoop(i) ? CORRECT : INCORRECT;
//}

//bool Parser::CheckTermLoop(int& i) {
//    if(!tokens_.CompareTypeWithRollback(MUL_OP) &&
//       !tokens_.CompareTypeWithRollback(DIV_OP))
//    {
//        return true;
//    }
//    int res = 0;
//    ParsingResult fact_res = ParseFactor(res);
//    if(fact_res != CORRECT) { return false; }
//    i *= res;
//    return CheckTermLoop(i);
//}

//ParsingResult Parser::ParseFactor(int& i) {
//    if(tokens_.CompareTypeWithRollback(NUMBER)) {
//        i = atoi(tokens_.val().c_str());
//        return CORRECT; }
//    ParsingResult func_call_res = ParseFuncCall();
//    if(func_call_res != NOT_MATCHED) {
//        return func_call_res == CORRECT ? CORRECT : INCORRECT;
//    }
//    if(tokens_.CompareTypeWithRollback(ID)) { return CORRECT; }
//    if(!tokens_.CompareTypeWithRollback(OPEN_BRACE)) { return NOT_MATCHED; }
//    ParsingResult arithm_expr_res = ParseArithmExpr(i);
//    if(arithm_expr_res != CORRECT) {
//        return INCORRECT;
//    }
//    return tokens_.NextTokenTypeEqualsTo(CLOSE_BRACE) ? CORRECT : INCORRECT;
//}

