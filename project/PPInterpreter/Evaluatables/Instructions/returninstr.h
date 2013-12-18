#ifndef RETURNINSTR_H
#define RETURNINSTR_H

#include "instruction.h"
#include "Evaluatables/evaluatable.h"

class ReturnInstr : public Evaluatable {
  public:
    ReturnInstr(PtrEval expr, InstructionBlock* parent) : expr_(expr), parent_(parent) {}
//    bool IsReturnInstruction() { return true; }
    int Evaluate(Scope &scope, Error &error);

  private:
    PtrEval expr_;
    InstructionBlock* parent_;
};

#endif // RETURNINSTR_H
