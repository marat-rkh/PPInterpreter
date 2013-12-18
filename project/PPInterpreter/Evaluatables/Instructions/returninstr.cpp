#include "returninstr.h"

int ReturnInstr::Evaluate(Scope &scope, Error &error) {
    int value = expr_->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    if(parent_ != 0) {
        parent_->has_returned_ = true;
    }
    return value;
}
