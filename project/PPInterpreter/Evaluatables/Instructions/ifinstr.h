#ifndef IFINSTR_H
#define IFINSTR_H

#include "controlflowinstr.h"

class IfInstr : public ControlFlowInstr {
  public:
    IfInstr(Condition const& c, InstructionBlock const& body):
        ControlFlowInstr(c, body)
    {}
    /*virtual*/int accept(Visitor &v);
};

#endif // IFINSTR_H
