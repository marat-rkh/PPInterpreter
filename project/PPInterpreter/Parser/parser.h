#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "token.h"
#include "tokenstream.h"
#include "program.h"

#include "evaluatable.h"
#include "function.h"
#include "instruction.h"
#include "returninstr.h"
#include "printinstr.h"

#include <memory>

#define DISABLE_COPY_AND_ASSIGN(TypeName) \
    TypeName(TypeName const&); \
    void operator=(TypeName const&)

using std::vector;

enum ParsingResult {CORRECT, INCORRECT, NOT_MATCHED};

class Parser {
public:
    Parser(vector<Token> const& tokens):
        tokens_(tokens),
        current_line_(1),
        program_()
    {}
    size_t Parse();

private:
    DISABLE_COPY_AND_ASSIGN(Parser);

    ParsingResult ParseStmt();

    typedef bool (Parser::*CheckerFunc)();
    ParsingResult ParseFuncDecl();
    ParsingResult ParseFuncHeader(CheckerFunc checker_func);

    bool CheckFuncDeclParams();
    bool CheckFuncDeclParamsLoop();
    bool CheckFuncCallParams();
    bool CheckFuncCallParamsLoop();
    bool CheckBlock();
    bool CheckBlockBody();

    ParsingResult ParseInstruction();
    ParsingResult ParseIOInstr();
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
