#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "Lexer/token.h"
#include "Parser/tokenstream.h"
#include "defines.h"
#include "program.h"
#include "error.h"
#include "Creators/funccreator.h"
#include "Creators/funccallcreator.h"
#include "expr.h"
#include "term.h"

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};

class Parser {
public:
    Parser(vector<Token> const& tokens):
        tokens_(tokens),
        current_line_(1)
    {}
    Program Parse(Error& error);

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt(InstructionBlock& program_body);
    ParsingResult ParseFuncDecl();

    template<class T>
    ParsingResult ParseFuncHeader(bool (Parser::*CheckerFunc)(T&), T& creator);

    bool CheckFuncDeclParams(FuncCreator& creator);
    bool CheckFuncDeclParamsLoop(FuncCreator& creator);
    bool CheckFuncCallParams(FuncCallCreator& creator);
    bool CheckFuncCallParamsLoop(FuncCallCreator& creator);
    bool CheckBlock(InstructionBlock& body);
    bool CheckBlockBody(InstructionBlock& body);

    ParsingResult ParseInstruction(InstructionBlock& body);
    ParsingResult ParseIOInstr(InstructionBlock& body);
    ParsingResult ParseControlFlowInstr(InstructionBlock& body);
    ParsingResult ParseAssignment(InstructionBlock& body);
    ParsingResult ParseReturnExpr(InstructionBlock& body);

    ParsingResult ParseExpr(Expr& expr);
    bool CheckExprLoop(Expr& expr);
    ParsingResult ParseTerm(Term& term);
    bool CheckTermLoop(Term& term);
    ParsingResult ParseFactor(Factor& term);

    TokenStream tokens_;
    size_t current_line_;
};

#endif // PARSER_H
