#ifndef IFINSTR_H
#define IFINSTR_H

#include "controlflowinstr.h"

class IfInstr : public ControlFlowInstr {
  public:
    IfInstr() {}
    IfInstr(Condition const& c, InstructionBlock const& body):
        ControlFlowInstr(c, body)
    {}
    IfInstr(IfInstr const& ii):
        ControlFlowInstr(ii)
    {}

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

#endif // IFINSTR_H
