#ifndef RETURNINSTR_H
#define RETURNINSTR_H

#include "instruction.h"
#include "evaluatable.h"

class ReturnInstr : public Instruction {
public:
    ReturnInstr(PtrEval expr) : expr_(expr) {}
    bool IsReturnInstruction() { return true; }
    int Evaluate(Scope &scope, const Params &params);

private:
    PtrEval expr_;
};

#endif // RETURNINSTR_H
