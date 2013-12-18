#include "function.h"

int Function::Evaluate(Scope &scope, Error& error) {
    local_scope_ = Scope(scope);
    if(local_scope_.size() != params_num_) {
        error.Set(Error::ARGNUMMISMATCH_ER, line_number_);
        return 0;
    }
    int value = body_.Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    if(body_.has_returned_) {
        return value;
    }
    return 0;
}
