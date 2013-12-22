#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "lexer.h"
#include "defines.h"
#include "error.h"
#include "ast.h"
#include "evaluator.h"

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};
typedef std::vector<Token>::iterator TokIterator;

class Parser {
public:
    Parser(): current_line_(1), error_occured_(false) {}
    Program Parse(vector<Token>& tokens);

    size_t current_line_;
    bool error_occured_;

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt(InstructionBlock& program_body, TokIterator& it);
    ParsingResult ParseFuncDecl(TokIterator& it);

    class FuncCreator;
    class FuncCallCreator;
    template<class T>
    ParsingResult ParseFuncHeader(bool (Parser::*CheckParams)(T&, TokIterator&), T& cr, TokIterator& it);

    bool CheckFuncDeclParams(FuncCreator& creator, TokIterator& it);
    bool CheckFuncDeclParamsLoop(FuncCreator& creator, TokIterator& it);
    bool CheckFuncCallParams(FuncCallCreator& creator, TokIterator& it);
    bool CheckFuncCallParamsLoop(FuncCallCreator& creator, TokIterator& it);
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

    class FuncCreator {
    public:
        void CreateWithBody(InstructionBlock const& body) {
            PtrVisitable func(new Function(body, params, line_number));
            FuncsScope::funcs.insert(std::pair<std::string, PtrVisitable> (id, func));
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
        std::vector<Expr> params;
    };
};

#endif // PARSER_H
