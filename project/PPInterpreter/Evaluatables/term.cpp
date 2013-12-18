#include "term.h"

Term::Term() {}

int Term::Evaluate(Scope &scope, Error& error) {
    int result = 1;
    std::string operation = "*";
    operations_.push_back("*");
    for(size_t i = 0; i != elements_.size(); ++i) {
        int value = elements_[i]->Evaluate(scope, error);
        if(error.IsOccured()) {
            return 0;
        }
        if(operation == "*") {
            result *= value;
        }
        else {
            if(value == 0) {
                error.Set(Error::DIVBYZERO_ER, elements_[i]->GetLineNumber());
                return 0;
            }
            result /= value;
        }
        operation = operations_[i];
    }
    return result;
}
