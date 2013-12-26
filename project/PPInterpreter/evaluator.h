#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <memory>
#include <stack>

#include "defines.h"
#include "ast.h"

typedef std::map<std::string, PtrVisitable> Scope;

class Evaluator : public Visitor {
public:
    Evaluator():
        Visitor(),
        scope_stack_(),
        error_(),
        return_instr_happened_(false)
    {
        Scope empty_scope;
        scope_stack_.push(empty_scope);
    }

    virtual int visit(Program *c);
    virtual int visit(Function *c);
    virtual int visit(InstructionBlock *c);
    virtual int visit(ReadInstr *c);
    virtual int visit(PrintInstr *c);
    virtual int visit(ReturnInstr *c);
    virtual int visit(Assignment *c);
    virtual int visit(FuncCall *c);
    virtual int visit(Variable *c);

    virtual int visit(ArithmExpr *c);
    virtual int visit(Factor *c);
    virtual int visit(Number *c);
    virtual int visit(Condition *c);
    virtual int visit(IfInstr *c);
    virtual int visit(WhileInstr *c);

private:
    int VisitExpr(ArithmExpr* c);
    int VisitTerm(ArithmExpr* c);

    std::stack<Scope> scope_stack_;
    Error error_;
    bool return_instr_happened_;
};

class FuncsScope {
public:
    static Scope funcs;
};

#endif // EVALUATOR_H
