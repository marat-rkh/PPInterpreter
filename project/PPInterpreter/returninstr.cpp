#include "returninstr.h"

int ReturnInstr::Evaluate(Scope &scope, const Params &params) {
    int value = expr_->Evaluate(scope, params);
    if(expr_->ErrorOccured()) {
        SetErrorFlag(expr_->GetErrorType());
        SetLineNumber(expr_->GetLineNumber());
        return 0;
    }
    return value;
}
