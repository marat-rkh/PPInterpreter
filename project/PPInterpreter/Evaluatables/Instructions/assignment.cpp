#include "assignment.h"

#include "evaluatable.h"
#include "number.h"

int Assignment::Evaluate(Scope &scope, Error& error) {
    int value = expr_->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    Scope::iterator it = scope.find(id_);

    PtrEval number(new Number(value));
    if(it == scope.end()) {
        scope.insert(std::pair<std::string, PtrEval>(id_, number));
    }
    else {
        it->second = number;
    }
    return 0;
}
