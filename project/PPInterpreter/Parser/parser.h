#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "Lexer/token.h"
#include "Parser/tokenstream.h"
#include "Evaluatables/program.h"
#include "defines.h"
#include "Creators/funccreator.h"
#include "Creators/funccallcreator.h"

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};

class Parser {
public:
    Parser(vector<Token> const& tokens):
        tokens_(tokens),
        current_line_(1)
    {}
    size_t Parse();

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt();
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
    ParsingResult ParseControlFlowInstr();
    ParsingResult ParseAssignment();
    ParsingResult ParseReturnExpr();

    ParsingResult ParseExpr();
    bool CheckExprLoop();
    ParsingResult ParseTerm();
    bool CheckTermLoop();
    ParsingResult ParseFactor();

    TokenStream tokens_;
    size_t current_line_;
    Program program_;
};

#endif // PARSER_H
