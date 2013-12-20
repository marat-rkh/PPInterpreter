#ifndef CONTROLFLOWINSTR_H
#define CONTROLFLOWINSTR_H


#include "condition.h"
#include "instructionblock.h"

class ControlFlowInstr: public Visitable {
  public:
    ControlFlowInstr(Condition const& c, InstructionBlock const& body):
        condition_(c),
        body_(body)
    {}
    Condition& condition() { return condition_; }
    InstructionBlock& body() { return body_; }

    int accept(Visitor &v) = 0;

  protected:
    Condition condition_;
    InstructionBlock body_;
};

#endif // CONTROLFLOWINSTR_H
