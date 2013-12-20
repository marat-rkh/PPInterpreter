#ifndef WHILEINSTR_H
#define WHILEINSTR_H

#include "controlflowinstr.h"

class WhileInstr: public ControlFlowInstr {
  public:
    WhileInstr(Condition const& c, InstructionBlock const& body):
        ControlFlowInstr(c, body)
    {}
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

#endif // WHILEINSTR_H
