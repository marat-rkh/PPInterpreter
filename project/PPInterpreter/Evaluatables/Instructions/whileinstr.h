#ifndef WHILEINSTR_H
#define WHILEINSTR_H

#include "controlflowinstr.h"

class WhileInstr : public ControlFlowInstr {
  public:
    WhileInstr(Condition const& c, InstructionBlock const& body, InstructionBlock* parent):
        ControlFlowInstr(c, body, parent)
    {}
    int Evaluate(Scope &scope, Error &error);
};

#endif // WHILEINSTR_H
