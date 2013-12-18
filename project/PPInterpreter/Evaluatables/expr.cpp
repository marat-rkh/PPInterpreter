#include "expr.h"

int Expr::Evaluate(Scope &scope, Error& error) {
    int result = 0;
    std::string operation = "+";
    operations_.push_back("+");
    for(size_t i = 0; i != elements_.size(); ++i) {
        int value = elements_[i]->Evaluate(scope, error);
        if(error.IsOccured()) {
            return 0;
        }
        if(operation == "+") {
            result += value;
        }
        else {
            result -= value;
        }
        operation = operations_[i];
    }
    return result;
}
