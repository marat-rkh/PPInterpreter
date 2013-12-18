#ifndef CONTROLFLOWINSTR_H
#define CONTROLFLOWINSTR_H

#include "Evaluatables/evaluatable.h"
#include "condition.h"
#include "Evaluatables/instructionblock.h"

class ControlFlowInstr : public Evaluatable {
  public:
    ControlFlowInstr(Condition const& c, InstructionBlock const& body, InstructionBlock* parent):
        condition_(c),
        body_(body),
        parent_(parent)
    {}
    int Evaluate(Scope &scope, Error &error) = 0;

  private:
    Condition condition_;
    InstructionBlock body_;
    InstructionBlock* parent_;
};

#endif // CONTROLFLOWINSTR_H
