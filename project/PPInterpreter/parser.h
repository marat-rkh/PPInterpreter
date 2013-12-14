#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "token.h"
#include "tokenstream.h"

#define DISABLE_COPY_AND_ASSIGN(TypeName) \
    TypeName(TypeName const&); \
    void operator=(TypeName const&)

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
    ParsingResult ParseFuncCall();
    bool CheckFuncParams();
    bool CheckBlock();
    bool CheckBlockBody();

    ParsingResult ParseInstruction();
    ParsingResult ParseIOInstr();
    ParsingResult ParseControlFlowInstr();
    ParsingResult ParseAssignment();
    ParsingResult ParseReturnExpr();

    ParsingResult ParseExpr();
    ParsingResult ParseArithmExpr();
    bool CheckArithmExprLoop();
    ParsingResult ParseTerm();
    bool CheckTermLoop();
    ParsingResult ParseFactor();

    TokenStream tokens_;
    size_t current_line_;
};

#endif // PARSER_H
