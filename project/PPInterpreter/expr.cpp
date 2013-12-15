#include "expr.h"

Expr::Expr() {}

int Expr::Evaluate(Scope &scope, const Params &params) {
    int result = 0;
    std::string operation = "+";
    operations_.push_back("+");
    for(size_t i = 0; i != elements_.size(); ++i) {
        int value = elements_[i]->Evaluate(scope, params);
        if(elements_[i]->ErrorOccured()) {
            SetErrorFlag(elements_[i]->GetErrorType());
            SetLineNumber(elements_[i]->GetLineNumber());
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
