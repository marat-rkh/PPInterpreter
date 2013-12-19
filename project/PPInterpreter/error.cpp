#include "error.h"

void Error::Set(ErrorType error_type, size_t line_number) {
    if(last_error_type_ == NOERRORS) {
        last_error_type_ = error_type;
        last_error_line_ = line_number;
    }
}

std::string Error::GetErrorMessage() {
    if(last_error_type_ == NOERRORS) {
        return "No errors occured";
    }
    std::string prefix = "line " + std::to_string(last_error_line_) + ": ";
    switch(last_error_type_)  {
    case SYNTAX_ER:
        return prefix + "syntax error";
    case DIVBYZERO_ER:
        return prefix + "division by zero";
    case UNDEFVAR_ER:
        return prefix + "undefined variable <name>";
    case UNDEFFUNC_ER:
        return prefix + "undefined function <name>";
    case ARGNUMMISMATCH_ER:
        return prefix + "arguments number mismatch for <name>";
    }
    return "";
}
