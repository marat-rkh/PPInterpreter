#include "parser.h"
#include "lexer.h"

Program Parser::Parse(vector<Token>& tokens) {
    InstructionBlock program_body;
    TokIterator it = tokens.begin();
    while(it != tokens.end()) {
        ParsingResult stmt_res = ParseStmt(program_body, it);
        if(stmt_res == INCORRECT || (it++)->type_ != NEWLINE) {
            error_occured_ = true;
            return Program();
        }
        ++current_line_;
    }
    return Program(program_body);
}

ParsingResult Parser::ParseStmt(InstructionBlock& program_body, TokIterator& it) {
    ParsingResult func_res = ParseFuncDecl(it);
    if(func_res != NOT_MATCHED) {
        return func_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult instr_res = ParseInstruction(program_body, it);
    if(instr_res != NOT_MATCHED) {
        return instr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseFuncDecl(TokIterator& it) {
    if(it->value_ != KEYWORDS[0]) {
        return NOT_MATCHED;
    }
    FuncCreator func_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncDeclParams, func_creator, ++it);
    if(func_res != CORRECT) { return INCORRECT; }
    InstructionBlock body;
    if(!CheckBlock(body, it)) { return INCORRECT; }
    func_creator.CreateWithBody(body);
    return CORRECT;
}

template<class T>
ParsingResult Parser::ParseFuncHeader(bool (Parser::*CheckParams)(T&, TokIterator&), T& cr, TokIterator& it) {
    TokIterator it_copy(it);
    if(it_copy->type_ != ID) { return NOT_MATCHED; }
    cr.id = it_copy->value_;
    cr.line_number = current_line_;
    if((++it_copy)->type_ != OPEN_BRACE) {
        return NOT_MATCHED;
    }
    if(!(this->*CheckParams)(cr, ++it_copy) || it_copy->type_ != CLOSE_BRACE) {
        return INCORRECT;
    }
    it = ++it_copy;
    return CORRECT;
}

bool Parser::CheckFuncDeclParams(FuncCreator& creator, TokIterator& it) {
    if(it->type_ != ID) {
        return true;
    }
    creator.params.push_back(it->value_);
    return CheckFuncDeclParamsLoop(creator, ++it) ? true : false;
}

bool Parser::CheckFuncDeclParamsLoop(FuncCreator& creator, TokIterator& it) {
    if(it->type_ != COMMA) {
        return true;
    }
    else if((++it)->type_ != ID) {
        return false;
    }
    creator.params.push_back(it->value_);
    return CheckFuncDeclParamsLoop(creator, it);
}

bool Parser::CheckFuncCallParams(FuncCallCreator& creator, TokIterator& it) {
    Expr expr;
    ParsingResult expr_res = ParseExpr(expr, it);
    if(expr_res != CORRECT) {
        return expr_res == NOT_MATCHED;
    }
    creator.params.push_back(expr);
    return CheckFuncCallParamsLoop(creator, it) ? true : false;
}

bool Parser::CheckFuncCallParamsLoop(FuncCallCreator& creator, TokIterator& it) {
    if(it->type_ != COMMA) {
        return true;
    }
    else {
        Expr expr;
        ParsingResult expr_res = ParseExpr(expr, ++it);
        if(expr_res != CORRECT) {
            return false;
        }
        creator.params.push_back(expr);
    }
    return CheckFuncCallParamsLoop(creator, it);
}

bool Parser::CheckBlock(InstructionBlock& body, TokIterator& it) {
    if(it->type_ != COLUMN ||
       (++it)->type_ !=NEWLINE)
    {
        return false;
    }
    ++current_line_;
    return CheckBlockBody(body, ++it);
}

bool Parser::CheckBlockBody(InstructionBlock& body, TokIterator& it) {
    ParsingResult instr_res = ParseInstruction(body, it);
    if(instr_res == INCORRECT) {
        return false;
    }
    if(it->type_ != NEWLINE) {
       if(instr_res == CORRECT) {
           return false;
       }
       return (it++)->value_ == KEYWORDS[1];
    }
    ++current_line_;
    return CheckBlockBody(body, ++it);
}

ParsingResult Parser::ParseInstruction(InstructionBlock& body, TokIterator& it) {
    ParsingResult io_res = ParseIOInstr(body, it);
    if(io_res != NOT_MATCHED) {
        return io_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult contr_flow_res = ParseControlFlowInstr(body, it);
    if(contr_flow_res != NOT_MATCHED) {
        return contr_flow_res == CORRECT ? CORRECT : INCORRECT;
    }
    ParsingResult assign_res = ParseAssignment(body, it);
    if(assign_res != NOT_MATCHED) {
        return assign_res == CORRECT ? CORRECT : INCORRECT;
    }
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncCallParams, func_call_creator, it);
    if(func_res != NOT_MATCHED) {
        if(func_res == INCORRECT) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new FuncCall(func_call_creator.Create())));
        return CORRECT;
    }
    ParsingResult return_expr_res = ParseReturnExpr(body, it);
    if(return_expr_res != NOT_MATCHED) {
        return return_expr_res == CORRECT ? CORRECT : INCORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseIOInstr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ == KEYWORDS[6]) {
        if((++it)->type_ != ID) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new ReadInstr((it++)->value_, current_line_)));
        return CORRECT;
    }
    if(it->value_ == KEYWORDS[5]) {
        Expr expr;
        if(ParseExpr(expr, ++it) != CORRECT) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new PrintInstr(expr, current_line_)));
        return CORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseControlFlowInstr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ != KEYWORDS[2] &&
       it->value_ != KEYWORDS[3])
    {
        return NOT_MATCHED;
    }
    std::string instruction_type = it->value_;
    Expr left_expr;
    ParsingResult expr_res = ParseExpr(left_expr, ++it);
    if(expr_res == INCORRECT || expr_res == NOT_MATCHED) {
        return INCORRECT;
    }
    if(it->type_ != COMPARISON_OP) {
        return INCORRECT;
    }
    std::string comp_char = it->value_;

    Expr right_expr;
    expr_res = ParseExpr(right_expr, ++it);
    InstructionBlock cf_instr_body;
    if(expr_res == INCORRECT ||
       expr_res == NOT_MATCHED ||
       !CheckBlock(cf_instr_body, it))
    {
        return INCORRECT;
    }
    Condition cond(left_expr, right_expr, comp_char);
    if(instruction_type == "while") {
        WhileInstr while_instr(cond, cf_instr_body);
        body.AddInstruction(PtrVisitable(new WhileInstr(while_instr)));
    }
    else {
        IfInstr if_instr(cond, cf_instr_body);
        body.AddInstruction(PtrVisitable(new IfInstr(if_instr)));
    }
    return CORRECT;
}

ParsingResult Parser::ParseAssignment(InstructionBlock& body, TokIterator& it) {
    TokIterator it_copy(it);
    if(it_copy->type_ != ID) {
        return NOT_MATCHED;
    }
    std::string id = it_copy->value_;
    if((++it_copy)->type_ != ASSIGN_OP) {
        return NOT_MATCHED;
    }
    Expr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it_copy);
    if(expr_res == INCORRECT) {
        return INCORRECT;
    }
    Assignment assign(id, PtrVisitable(new Expr(expr)), current_line_);
    body.AddInstruction(PtrVisitable(new Assignment(assign)));
    it = it_copy;
    return CORRECT;
}

ParsingResult Parser::ParseReturnExpr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ != KEYWORDS[4]) {
        return NOT_MATCHED;
    }
    Expr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it);
    if(expr_res != NOT_MATCHED) {
        if(expr_res == INCORRECT) {
            return INCORRECT;
        }
        ReturnInstr ri(PtrVisitable(new Expr(expr)));
        body.AddInstruction(PtrVisitable(new ReturnInstr(ri)));
        return CORRECT;
    }
    if(it->type_ != NEWLINE) {
        return INCORRECT;
    }
    return CORRECT;
}

ParsingResult Parser::ParseExpr(Expr& expr, TokIterator& it) {
    expr.SetLineNumber(current_line_);
    Term term;
    ParsingResult term_res = ParseTerm(term, it);
    if(term_res != CORRECT) {
        return term_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
    }
    expr.AddTerm(term);
    return CheckExprLoop(expr, it) ? CORRECT : INCORRECT;
}

bool Parser::CheckExprLoop(Expr& expr, TokIterator& it) {
    if(it->type_ != PLUS_OP &&
       it->type_ != MINUS_OP)
    {
        return true;
    }
    expr.AddOperation(it->value_);
    Term term;
    ParsingResult term_res = ParseTerm(term, ++it);
    if(term_res != CORRECT) {
        return false;
    }
    expr.AddTerm(term);
    return CheckExprLoop(expr, it);
}

ParsingResult Parser::ParseTerm(Term& term, TokIterator& it) {
    term.SetLineNumber(current_line_);
    Factor factor;
    ParsingResult fact_res = ParseFactor(factor, it);
    if(fact_res != CORRECT) {
        return fact_res == NOT_MATCHED ? NOT_MATCHED : INCORRECT;
    }
    term.AddElem(PtrVisitable(new Factor(factor)));
    return CheckTermLoop(term, it) ? CORRECT : INCORRECT;
}

bool Parser::CheckTermLoop(Term& term, TokIterator& it) {
    if(it->type_ != MUL_OP &&
       it->type_ != DIV_OP)
    {
        return true;
    }
    term.AddOperation(it->value_);
    Factor factor;
    ParsingResult fact_res = ParseFactor(factor, ++it);
    if(fact_res != CORRECT) {
        return false;
    }
    term.AddElem(PtrVisitable(new Factor(factor)));
    return CheckTermLoop(term, it);
}

ParsingResult Parser::ParseFactor(Factor& factor, TokIterator& it) {
    if(it->type_ == MINUS_OP) {
        factor.SetUnaryOperator("-");
        ++it;
    }
    else if(it->type_ == PLUS_OP) {
        factor.SetUnaryOperator("+");
        ++it;
    }
    if(it->type_ == NUMBER) {
        factor.SetFactExpr(PtrVisitable(new Number(it->value_)));
        ++it;
        return CORRECT;
    }
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncHeader(&Parser::CheckFuncCallParams, func_call_creator, it);
    if(func_res != NOT_MATCHED) {
        if(func_res != CORRECT) {
            return INCORRECT;
        }
        factor.SetFactExpr(PtrVisitable(new FuncCall(func_call_creator.Create())));
        return CORRECT;
    }
    if(it->type_ == ID) {
        factor.SetFactExpr(PtrVisitable(new Variable(it->value_, current_line_)));
        ++it;
        return CORRECT;
    }
    if(it->type_ != OPEN_BRACE) {
        return NOT_MATCHED;
    }
    Expr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it);
    if(expr_res != CORRECT) {
        return INCORRECT;
    }
    factor.SetFactExpr(PtrVisitable(new Expr(expr)));
    return ((it++)->type_ == CLOSE_BRACE) ? CORRECT : INCORRECT;
}
