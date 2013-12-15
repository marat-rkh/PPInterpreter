#include "program.h"

Program::Program() {
}

int Program::Evaluate(Scope &scope, const Params &params) {
    for(size_t i = 0; i != instructions_.size(); ++i) {
        instructions_[i]->Evaluate(scope, params);
        if(instructions_[i]->ErrorOccured()) {
            SetErrorFlag(instructions_[i]->GetErrorType());
            SetLineNumber(instructions_[i]->GetLineNumber());
            return 0;
        }
        if(instructions_[i]->IsReturnInstruction()) { return 0; }
    }
    return 0;
}
