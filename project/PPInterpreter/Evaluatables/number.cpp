#include "number.h"

#include <cstdlib>

Number::Number(std::string const& num) {
    value_ = 1;
    int first_num_position = 0;
    if(num[0] == '-') {
        value_ = -1;
        first_num_position = 1;
    }
    std::string substring = num.substr(first_num_position, num.size());
    value_ *= atoi(substring.c_str());
}
