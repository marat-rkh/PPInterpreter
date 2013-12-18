#include "printinstr.h"
#include <iostream>

int PrintInstr::Evaluate(Scope &scope, Error &error) {
    int value = expr_->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    std::cout << value;
    return 0;
}
