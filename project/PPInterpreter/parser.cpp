#include "parser.h"
#include "lexer.h"

class FuncCreator {
public:
    void CreateWithBody(InstructionBlock const& body) {
        PtrVisitable func(new Function(body, params, line_number));
        Evaluator::funcs.insert(std::pair<std::string, PtrVisitable> (id, func));
    }
    std::string id;
    size_t line_number;
    std::vector<std::string> params;
};

class FuncCallCreator {
public:
    FuncCall Create() {
        return FuncCall(id, params, line_number);
    }
    std::string id;
    size_t line_number;
    std::vector<ArithmExpr> params;
};

Program Parser::Parse(vector<Token> const& tokens) {
    current_line_ = 1;
    error_occured_ = false;
    Evaluator::funcs.empty();
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
        return func_res;
    }
    ParsingResult instr_res = ParseInstruction(program_body, it);
    if(instr_res != NOT_MATCHED) {
        return instr_res;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseFuncDecl(TokIterator& it) {
    if(it->value_ != "def") {
        return NOT_MATCHED;
    }
    FuncCreator func_creator;
    ParsingResult func_res = ParseFuncDeclHeader(func_creator, ++it);
    if(func_res != CORRECT) { return INCORRECT; }
    InstructionBlock body;
    if(!ParseBlock(body, it)) { return INCORRECT; }
    func_creator.CreateWithBody(body);
    return CORRECT;
}

ParsingResult Parser::ParseFuncDeclHeader(FuncCreator& cr, TokIterator& it) {
    if(ParseFuncName(cr, it) == NOT_MATCHED) {
        return NOT_MATCHED;
    }
    if(!ParseFuncDeclParams(cr, it) || it->type_ != CLOSE_BRACE) {
        return INCORRECT;
    }
    ++it;
    return CORRECT;
}

template<class T>
ParsingResult Parser::ParseFuncName(T& cr, TokIterator& it) {
    TokIterator it_copy(it);
    if(it_copy->type_ != ID) {
        return NOT_MATCHED;
    }
    cr.id = it_copy->value_;
    cr.line_number = current_line_;
    if((++it_copy)->type_ != OPEN_BRACE) {
        return NOT_MATCHED;
    }
    it = ++it_copy;
    return CORRECT;
}

bool Parser::ParseFuncDeclParams(FuncCreator& creator, TokIterator& it) {
    if(it->type_ != ID) {
        return true;
    }
    creator.params.push_back(it->value_);
    return ParseFuncDeclParamsLoop(creator, ++it) ? true : false;
}

bool Parser::ParseFuncDeclParamsLoop(FuncCreator& creator, TokIterator& it) {
    if(it->type_ != COMMA) {
        return true;
    }
    else if((++it)->type_ != ID) {
        return false;
    }
    creator.params.push_back(it->value_);
    return ParseFuncDeclParamsLoop(creator, it);
}

ParsingResult Parser::ParseFuncCallHeader(FuncCallCreator& cr, TokIterator& it) {
    if(ParseFuncName(cr, it) == NOT_MATCHED) {
        return NOT_MATCHED;
    }
    if(!ParseFuncCallParams(cr, it) || it->type_ != CLOSE_BRACE) {
        return INCORRECT;
    }
    ++it;
    return CORRECT;
}

bool Parser::ParseFuncCallParams(FuncCallCreator& creator, TokIterator& it) {
    ArithmExpr expr;
    ParsingResult expr_res = ParseExpr(expr, it);
    if(expr_res != CORRECT) {
        return expr_res == NOT_MATCHED;
    }
    creator.params.push_back(expr);
    return ParseFuncCallParamsLoop(creator, it) ? true : false;
}

bool Parser::ParseFuncCallParamsLoop(FuncCallCreator& creator, TokIterator& it) {
    if(it->type_ != COMMA) {
        return true;
    }
    else {
        ArithmExpr expr;
        ParsingResult expr_res = ParseExpr(expr, ++it);
        if(expr_res != CORRECT) {
            return false;
        }
        creator.params.push_back(expr);
    }
    return ParseFuncCallParamsLoop(creator, it);
}

bool Parser::ParseBlock(InstructionBlock& body, TokIterator& it) {
    if(it->type_ != COLUMN ||
       (++it)->type_ !=NEWLINE)
    {
        return false;
    }
    ++current_line_;
    return ParseBlockBody(body, ++it);
}

bool Parser::ParseBlockBody(InstructionBlock& body, TokIterator& it) {
    ParsingResult instr_res = ParseInstruction(body, it);
    if(instr_res == INCORRECT) {
        return false;
    }
    if(it->type_ != NEWLINE) {
       if(instr_res == CORRECT) {
           return false;
       }
       return (it++)->value_ =="end";
    }
    ++current_line_;
    return ParseBlockBody(body, ++it);
}

ParsingResult Parser::ParseInstruction(InstructionBlock& body, TokIterator& it) {
    ParsingResult io_res = ParseIOInstr(body, it);
    if(io_res != NOT_MATCHED) {
        return io_res;
    }
    ParsingResult contr_flow_res = ParseControlFlowInstr(body, it);
    if(contr_flow_res != NOT_MATCHED) {
        return contr_flow_res;
    }
    ParsingResult assign_res = ParseAssignment(body, it);
    if(assign_res != NOT_MATCHED) {
        return assign_res;
    }
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncCallHeader(func_call_creator, it);
    if(func_res != NOT_MATCHED) {
        if(func_res == INCORRECT) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new FuncCall(func_call_creator.Create())));
        return CORRECT;
    }
    ParsingResult return_expr_res = ParseReturnExpr(body, it);
    if(return_expr_res != NOT_MATCHED) {
        return return_expr_res;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseIOInstr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ == "read") {
        if((++it)->type_ != ID) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new ReadInstr((it++)->value_, current_line_)));
        return CORRECT;
    }
    if(it->value_ == "print") {
        ArithmExpr expr;
        if(ParseExpr(expr, ++it) != CORRECT) {
            return INCORRECT;
        }
        body.AddInstruction(PtrVisitable(new PrintInstr(expr, current_line_)));
        return CORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseControlFlowInstr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ != "if" &&
            it->value_ != "while")
    {
        return NOT_MATCHED;
    }
    std::string instruction_type = it->value_;
    ArithmExpr left_expr;
    ParsingResult expr_res = ParseExpr(left_expr, ++it);
    if(expr_res == INCORRECT || expr_res == NOT_MATCHED) {
        return INCORRECT;
    }
    if(it->type_ != COMPARISON_OP) {
        return INCORRECT;
    }
    std::string comp_char = it->value_;

    ArithmExpr right_expr;
    expr_res = ParseExpr(right_expr, ++it);
    InstructionBlock cf_instr_body;
    if(expr_res == INCORRECT ||
       expr_res == NOT_MATCHED ||
       !ParseBlock(cf_instr_body, it))
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
    ArithmExpr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it_copy);
    if(expr_res == INCORRECT) {
        return INCORRECT;
    }
    Assignment assign(id, PtrVisitable(new ArithmExpr(expr)), current_line_);
    body.AddInstruction(PtrVisitable(new Assignment(assign)));
    it = it_copy;
    return CORRECT;
}

ParsingResult Parser::ParseReturnExpr(InstructionBlock& body, TokIterator& it) {
    if(it->value_ != "return") {
        return NOT_MATCHED;
    }
    ArithmExpr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it);
    if(expr_res != NOT_MATCHED) {
        if(expr_res == INCORRECT) {
            return INCORRECT;
        }
        ReturnInstr ri(PtrVisitable(new ArithmExpr(expr)));
        body.AddInstruction(PtrVisitable(new ReturnInstr(ri)));
        return CORRECT;
    }
    if(it->type_ != NEWLINE) {
        return INCORRECT;
    }
    return CORRECT;
}

ParsingResult Parser::ParseExpr(ArithmExpr& expr, TokIterator& it) {
    expr.SetLineNumber(current_line_);
    ArithmExpr term;
    ParsingResult term_res = ParseTerm(term, it);
    if(term_res != CORRECT) {
        return term_res;
    }
    expr.AddElem(PtrVisitable(new ArithmExpr(term)));
    return ParseExprLoop(expr, it) ? CORRECT : INCORRECT;
}

bool Parser::ParseExprLoop(ArithmExpr& expr, TokIterator& it) {
    if(it->type_ != PLUS_OP &&
       it->type_ != MINUS_OP)
    {
        return true;
    }
    expr.AddOperation(it->value_);
    ArithmExpr term;
    ParsingResult term_res = ParseTerm(term, ++it);
    if(term_res != CORRECT) {
        return false;
    }
    expr.AddElem(PtrVisitable(new ArithmExpr(term)));
    return ParseExprLoop(expr, it);
}

ParsingResult Parser::ParseTerm(ArithmExpr& term, TokIterator& it) {
    term.SetLineNumber(current_line_);
    ParsingResult fact_res = ParseFactor(term, it);
    if(fact_res != CORRECT) {
        return fact_res;
    }
//    term.AddElem(PtrVisitable(new Factor(factor)));
    return ParseTermLoop(term, it) ? CORRECT : INCORRECT;
}

bool Parser::ParseTermLoop(ArithmExpr& term, TokIterator& it) {
    if(it->type_ != MUL_OP &&
       it->type_ != DIV_OP)
    {
        return true;
    }
    term.AddOperation(it->value_);
//    Factor factor;
    ParsingResult fact_res = ParseFactor(term, ++it);
    if(fact_res != CORRECT) {
        return false;
    }
//    term.AddElem(PtrVisitable(new Factor(factor)));
    return ParseTermLoop(term, it);
}

ParsingResult Parser::ParseFactor(ArithmExpr& term, TokIterator& it) {
    bool is_unary_minus = false;
    if(it->type_ == MINUS_OP) {
        is_unary_minus = true;
        ++it;
    }
    if(it->type_ == NUMBER) {
        PtrVisitable PtrNum = PtrVisitable(new Number((it++)->value_));
        if(is_unary_minus) {
            PtrNum = PtrVisitable(new UnaryMinExpr(PtrNum));
        }
        term.AddElem(PtrNum);
        return CORRECT;
    }
    ParsingResult func_call_res = ParseFactorFuncCall(term, it, is_unary_minus);
    if(func_call_res != NOT_MATCHED) {
        return func_call_res;
    }
    if(it->type_ == ID) {
        PtrVisitable PtrVar = PtrVisitable(new Variable((it++)->value_, current_line_));
        if(is_unary_minus) {
            PtrVar = PtrVisitable(new UnaryMinExpr(PtrVar));
        }
        term.AddElem(PtrVar);
        return CORRECT;
    }
    return ParseExprInParanthesis(term, it, is_unary_minus);
}

ParsingResult Parser::ParseFactorFuncCall(ArithmExpr& term, TokIterator &it, bool is_unary_minus) {
    FuncCallCreator func_call_creator;
    ParsingResult func_res = ParseFuncCallHeader(func_call_creator, it);
    if(func_res != NOT_MATCHED) {
        if(func_res != CORRECT) {
            return INCORRECT;
        }
        PtrVisitable PtrFuncCall = PtrVisitable(new FuncCall(func_call_creator.Create()));
        if(is_unary_minus) {
            PtrFuncCall = PtrVisitable(new UnaryMinExpr(PtrFuncCall));
        }
        term.AddElem(PtrFuncCall);
        return CORRECT;
    }
    return NOT_MATCHED;
}

ParsingResult Parser::ParseExprInParanthesis(ArithmExpr& term, TokIterator &it, bool is_unary_minus) {
    if(it->type_ != OPEN_BRACE) {
        return NOT_MATCHED;
    }
    ArithmExpr expr;
    ParsingResult expr_res = ParseExpr(expr, ++it);
    if(expr_res != CORRECT) {
        return INCORRECT;
    }
    PtrVisitable PtrExpr = PtrVisitable(new ArithmExpr(expr));
    if(is_unary_minus) {
        PtrExpr = PtrVisitable(new UnaryMinExpr(PtrExpr));
    }
    term.AddElem(PtrExpr);
    return (it++)->type_ == CLOSE_BRACE ? CORRECT : INCORRECT;
}
//class FuncCreator;
//class FuncCallCreator;
