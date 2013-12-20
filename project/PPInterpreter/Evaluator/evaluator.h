#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "visitor.h"

#include <memory>
#include <stack>

#include "visitable.h"
#include "error.h"
#include "globalscope.h"

typedef std::shared_ptr<Function> PtrFunc;
typedef std::map<std::string, PtrFunc> GSFuncs;

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

    /*virtual*/int visit(Program *c);
    /*virtual*/int visit(Function *c);
    /*virtual*/int visit(InstructionBlock *c);
    /*virtual*/int visit(ReadInstr *c);
    /*virtual*/int visit(PrintInstr *c);
    /*virtual*/int visit(ReturnInstr *c);
    /*virtual*/int visit(Assignment *c);
    /*virtual*/int visit(FuncCall *c);
    /*virtual*/int visit(Variable *c);
    /*virtual*/int visit(Expr *c);
    /*virtual*/int visit(Term *c);
    /*virtual*/int visit(Number *c);
    /*virtual*/int visit(Condition *c);
    /*virtual*/int visit(IfInstr *c);
    /*virtual*/int visit(WhileInstr *c);

private:
    std::stack<Scope> scope_stack_;
    Error error_;
    bool return_instr_happened_;
};

#endif // EVALUATOR_H
