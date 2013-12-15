#include "number.h"

#include <cstdlib>

Number::Number(std::string const& num) {
    value_ = 1;
    if(num[0] == '-') { value_ = -1; }
    std::string substring = num.substr(1, num.size());
    value_ *= atoi(substring.c_str());
}

int Number::Evaluate(Scope &scope, const Params &params) {
    return value_;
}
