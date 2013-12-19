#include "function.h"

int Function::Evaluate(Scope &scope, Error& error) {
    int value = body_.Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    if(body_.has_returned_) {
        return value;
    }
    return 0;
}
