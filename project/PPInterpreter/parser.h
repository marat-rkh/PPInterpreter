#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "lexer.h"
#include "defines.h"
#include "error.h"
#include "Visitables/program.h"
#include "Visitables/expr.h"
#include "Visitables/term.h"
#include "Visitables/funccall.h"
#include "Visitables/function.h"
#include "evaluator.h"

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};
typedef std::vector<Token>::iterator TokIterator;

class Parser {
public:
    Parser(): current_line_(1) {}
    Program Parse(vector<Token>& tokens, Error& error);

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt(InstructionBlock& program_body, TokIterator& it);
    ParsingResult ParseFuncDecl(TokIterator& it);

    class Creator;
    ParsingResult ParseFuncHeader(bool (Parser::*ParamsChecker)(Creator&, TokIterator&),
                                  Creator& creator,
                                  TokIterator& it);

    bool CheckFuncDeclParams(Creator& creator, TokIterator& it);
    bool CheckFuncDeclParamsLoop(Creator& creator, TokIterator& it);
    bool CheckFuncCallParams(Creator& creator, TokIterator& it);
    bool CheckFuncCallParamsLoop(Creator& creator, TokIterator& it);
    bool CheckBlock(InstructionBlock& body, TokIterator& it);
    bool CheckBlockBody(InstructionBlock& body, TokIterator& it);

    ParsingResult ParseInstruction(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseIOInstr(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseControlFlowInstr(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseAssignment(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseReturnExpr(InstructionBlock& body, TokIterator& it);

    ParsingResult ParseExpr(Expr& expr, TokIterator& it);
    bool CheckExprLoop(Expr& expr, TokIterator& it);
    ParsingResult ParseTerm(Term& term, TokIterator& it);
    bool CheckTermLoop(Term& term, TokIterator& it);
    ParsingResult ParseFactor(Factor& term, TokIterator& it);

    size_t current_line_;

    class Creator {
    public:
        Creator() {}
        void SetIDAndLine(std::string id, size_t line_num) {
            id_ = id;
            line_number_ = line_num;
        }
        void AddParam(Expr const& expr) { call_params_.push_back(expr); }
        void AddParam(std::string param_name) { params_.push_back(param_name); }
        FuncCall Create() { return FuncCall(id_, call_params_, line_number_); }
        void CreateWithBody(InstructionBlock const& body) {
            PtrFunc func(new Function(body, params_, line_number_));
            GlobalScope::GetInstance().gs_funcs.insert(std::pair<std::string, PtrFunc> (id_, func));
        }
    private:
        std::string id_;
        size_t line_number_;
        std::vector<Expr> call_params_;
        std::vector<std::string> params_;
    };
};

#endif // PARSER_H
