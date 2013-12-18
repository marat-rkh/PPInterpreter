#include "condition.h"

int Condition::Evaluate(Scope &scope, Error &error) {
    int value1 = e1_.Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    int value2 = e2_.Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    if(comp_char_ == ">") {
        return value1 > value2 ? 1 : 0;
    }
    if(comp_char_ == "<") {
        return value1 < value2 ? 1 : 0;
    }
    if(comp_char_ == ">=") {
        return value1 >= value2 ? 1 : 0;
    }
    if(comp_char_ == "<=") {
        return value1 <= value2 ? 1 : 0;
    }
    if(comp_char_ == "==") {
        return value1 == value2 ? 1 : 0;
    }
    if(comp_char_ == "!=") {
        return value1 != value2 ? 1 : 0;
    }
}
