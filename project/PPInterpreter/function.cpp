#include "function.h"

int Function::Evaluate(Scope &scope, const Params &params) {
    local_scope_ = Scope(scope);
    if(local_scope_.size() != params_num_) {
        SetErrorFlag(ARGNUMMISMATCH_ER);
        return 0;
    }
    for(size_t i = 0; i != instructions_.size(); ++i) {
        int value = instructions_[i]->Evaluate(local_scope_, params);
        if(instructions_[i]->ErrorOccured()) {
            SetErrorFlag(instructions_[i]->GetErrorType());
            SetLineNumber(instructions_[i]->GetLineNumber());
            return 0;
        }
        if(instructions_[i]->IsReturnInstruction()) { return value; }
    }
    return 0;
}
