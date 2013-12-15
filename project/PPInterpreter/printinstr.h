#ifndef PRINTINSTR_H
#define PRINTINSTR_H

#include "instruction.h"
#include "evaluatable.h"

class PrintInstr : public Instruction {
public:
    PrintInstr(PtrEval expr) : expr_(expr) {}
    bool IsReturnInstruction() { return false; }
    int Evaluate(Scope &scope, const Params &params);

private:
    PtrEval expr_;
};

#endif // PRINTINSTR_H
