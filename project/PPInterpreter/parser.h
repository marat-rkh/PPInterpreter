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
typedef std::vector<Token>::const_iterator TokIterator;

class Parser {
public:
    Parser(): current_line_(1), error_occured_(false) {}
    Program Parse(vector<Token> const& tokens);

    size_t current_line_;
    bool error_occured_;

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt(InstructionBlock& program_body, TokIterator& it);
    ParsingResult ParseFuncDecl(TokIterator& it);

    class FuncCreator;
    class FuncCallCreator;
    template<class T>
    ParsingResult ParseFuncHeader(bool (Parser::*ParseParams)(T&, TokIterator&), T& cr, TokIterator& it);

    bool ParseFuncDeclParams(FuncCreator& creator, TokIterator& it);
    bool ParseFuncDeclParamsLoop(FuncCreator& creator, TokIterator& it);
    bool ParseFuncCallParams(FuncCallCreator& creator, TokIterator& it);
    bool ParseFuncCallParamsLoop(FuncCallCreator& creator, TokIterator& it);
    bool ParseBlock(InstructionBlock& body, TokIterator& it);
    bool ParseBlockBody(InstructionBlock& body, TokIterator& it);

    ParsingResult ParseInstruction(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseIOInstr(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseControlFlowInstr(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseAssignment(InstructionBlock& body, TokIterator& it);
    ParsingResult ParseReturnExpr(InstructionBlock& body, TokIterator& it);

    ParsingResult ParseExpr(ArithmExpr& expr, TokIterator& it);
    bool ParseExprLoop(ArithmExpr& expr, TokIterator& it);
    ParsingResult ParseTerm(ArithmExpr& term, TokIterator& it);
    bool ParseTermLoop(ArithmExpr& term, TokIterator& it);

    ParsingResult ParseFactor(Factor& term, TokIterator& it);
    ParsingResult ParseExprInParanthesis(Factor& factor, TokIterator& it);
    ParsingResult ParseFactorFuncCall(Factor& factor, TokIterator& it);

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
        std::vector<ArithmExpr> params;
    };
};

#endif // PARSER_H
