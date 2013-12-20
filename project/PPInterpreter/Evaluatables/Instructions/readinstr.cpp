#include "readinstr.h"

#include <iostream>
#include "number.h"

int ReadInstr::Evaluate(Scope &scope, Error &error) {
    Scope::iterator it = scope.find(id_);
    if(it == scope.end()) {
        error.Set(Error::UNDEFVAR_ER, line_number_);
        return 0;
    }
    int input = 0;
    std::cin >> input;
    PtrEval number(new Number(input));
    it->second = number;
    return 0;
}
