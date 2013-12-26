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

class FuncCreator;
class FuncCallCreator;

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
    ParsingResult ParseFuncDeclHeader(FuncCreator& cr, TokIterator& it);
    template<class T>
    ParsingResult ParseFuncName(T& cr, TokIterator& it);
    bool ParseFuncDeclParams(FuncCreator& creator, TokIterator& it);
    bool ParseFuncDeclParamsLoop(FuncCreator& creator, TokIterator& it);

    ParsingResult ParseFuncCallHeader(FuncCallCreator& cr, TokIterator& it);
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

    ParsingResult ParseFactor(ArithmExpr& term, TokIterator& it);
    ParsingResult ParseExprInParanthesis(ArithmExpr& term, TokIterator& it, bool is_unary_minus);
    ParsingResult ParseFactorFuncCall(ArithmExpr& term, TokIterator& it, bool is_unary_minus);
};

#endif // PARSER_H
