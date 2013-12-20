#ifndef RETURNINSTR_H
#define RETURNINSTR_H

#include "Evaluatables/evaluatable.h"
#include "Evaluatables/instructionblock.h"
#include <iostream>

class ReturnInstr : public Evaluatable {
  public:
    ReturnInstr(PtrEval expr, InstructionBlock* parent) : expr_(expr), parent_(parent) {}
    ReturnInstr(ReturnInstr const& ri):
        Evaluatable(ri),
        expr_(ri.expr_),
        parent_(ri.parent_)
    {}
    int Evaluate(Scope &scope, Error &error);

  private:
    PtrEval expr_;
    InstructionBlock* parent_;
};

#endif // RETURNINSTR_H
