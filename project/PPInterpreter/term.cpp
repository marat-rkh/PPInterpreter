#include "term.h"

Term::Term() {}

int Term::Evaluate(Scope &scope, const Params &params) {
    int result = 1;
    std::string operation = "*";
    operations_.push_back("*");
    for(size_t i = 0; i != elements_.size(); ++i) {
        int value = elements_[i]->Evaluate(scope, params);
        if(elements_[i]->ErrorOccured()) {
            SetErrorFlag(elements_[i]->GetErrorType());
            SetLineNumber(elements_[i]->GetLineNumber());
            return 0;
        }
        if(operation == "*") {
            result *= value;
        }
        else {
            if(value == 0) {
                SetErrorFlag(DIVBYZERO_ER);
                SetLineNumber(elements_[i]->GetLineNumber());
                return 0;
            }
            result /= value;
        }
        operation = operations_[i];
    }
    return result;
}
