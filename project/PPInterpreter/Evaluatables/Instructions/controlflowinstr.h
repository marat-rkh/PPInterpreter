#ifndef CONTROLFLOWINSTR_H
#define CONTROLFLOWINSTR_H

#include "visitable.h"
#include "condition.h"
#include "instructionblock.h"

class ControlFlowInstr: public Visitable {
  public:
    ControlFlowInstr() {}
    ControlFlowInstr(Condition const& c, InstructionBlock const& body):
        condition_(c),
        body_(body)
    {}
    ControlFlowInstr(ControlFlowInstr const& cfi):
        Visitable(cfi),
        condition_(cfi.condition_),
        body_(cfi.body_)
    {}

    Condition& condition() { return condition_; }
    InstructionBlock& body() { return body_; }

    int accept(Visitor &v) = 0;

  protected:
    Condition condition_;
    InstructionBlock body_;
};

#endif // CONTROLFLOWINSTR_H
