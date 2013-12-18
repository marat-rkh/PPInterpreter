#include "ifinstr.h"

int IfInstr::Evaluate(Scope &scope, Error &error) {
    int is_true = condition_.Evaluate(scope, error);
    if(error.IsOccured() || !is_true) {
        return 0;
    }
    int value = body_.Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    if(parent_ != 0) {
        parent_->has_returned_ = body_.has_returned_;
    }
    return value;
}
