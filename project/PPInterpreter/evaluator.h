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

    virtual int visit(Program *c) override;
    virtual int visit(Function *c) override;
    virtual int visit(InstructionBlock *c) override;
    virtual int visit(ReadInstr *c) override;
    virtual int visit(PrintInstr *c) override;
    virtual int visit(ReturnInstr *c) override;
    virtual int visit(Assignment *c) override;
    virtual int visit(FuncCall *c) override;
    virtual int visit(Variable *c) override;

    virtual int visit(ArithmExpr *c) override;
    virtual int visit(UnaryMinExpr *c) override;
    virtual int visit(Number *c) override;
    virtual int visit(Condition *c) override;
    virtual int visit(IfInstr *c) override;
    virtual int visit(WhileInstr *c) override;

    static Scope funcs;
private:
    int VisitExpr(ArithmExpr* c);
    int VisitTerm(ArithmExpr* c);

    std::stack<Scope> scope_stack_;
    Error error_;
    bool return_instr_happened_;
};

#endif // EVALUATOR_H
