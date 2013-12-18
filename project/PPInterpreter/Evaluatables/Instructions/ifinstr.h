#ifndef IFINSTR_H
#define IFINSTR_H

#include "controlflowinstr.h"

class IfInstr : public ControlFlowInstr {
  public:
    IfInstr(Condition const& c, InstructionBlock const& body, InstructionBlock* parent):
        ControlFlowInstr(c, body, parent)
    {}
    int Evaluate(Scope &scope, Error &error);
};

#endif // IFINSTR_H
