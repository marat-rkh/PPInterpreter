#include "whileinstr.h"

int WhileInstr::Evaluate(Scope &scope, Error &error) {
    int is_true;
    while((is_true = condition_.Evaluate(scope, error)) && !error.IsOccured()) {
        int value = body_.Evaluate(scope, error);
        if(error.IsOccured()) {
            return 0;
        }
        if(body_.has_returned_ && parent_ != 0) {
            parent_->has_returned_ = body_.has_returned_;
            return value;
        }
    }
    return 0;
}
