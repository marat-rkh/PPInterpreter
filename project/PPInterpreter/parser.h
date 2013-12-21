#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "token.h"
#include "tokenstream.h"
#include "defines.h"
#include "Visitables/program.h"
#include "error.h"
#include "funccreator.h"
#include "funccallcreator.h"
#include "Visitables/expr.h"
#include "Visitables/term.h"

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};
typedef std::vector<Token>::iterator TokIterator;

class Parser {
public:
//    Parser(vector<Token> const& tokens):
//        tokens_(tokens),
//        current_line_(1)
//    {}
    Parser(): current_line_(1) {}
    Program Parse(vector<Token>& tokens, Error& error);

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt(InstructionBlock& program_body, TokIterator& it);
    ParsingResult ParseFuncDecl(TokIterator& it);

    template<class T>
    ParsingResult ParseFuncHeader(bool (Parser::*CheckerFunc)(T&, TokIterator&), T& creator, TokIterator& it);

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

//    TokenStream tokens_;
    size_t current_line_;
};

#endif // PARSER_H
