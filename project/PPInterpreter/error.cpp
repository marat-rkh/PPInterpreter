#include "error.h"

void Error::Set(ErrorType error_type, size_t line_number) {
    if(last_error_type_ == NOERRORS) {
        last_error_type_ = error_type;
        last_error_line_ = line_number;
    }
}

void Error::Set(ErrorType error_type, size_t line_number, std::string add_info) {
    Set(error_type, line_number);
    additional_info_ = add_info;
}

std::string Error::GetErrorMessage() {
    std::string prefix = "\nline " + std::to_string(last_error_line_) + ": ";
    switch(last_error_type_)  {
    case SYNTAX_ER:
        return prefix + "syntax error";
    case DIVBYZERO_ER:
        return prefix + "division by zero";
    case UNDEFVAR_ER:
        return prefix + "undefined variable '" + additional_info_ + "'";
    case UNDEFFUNC_ER:
        return prefix + "undefined function '" + additional_info_ + "'";
    case ARGNUMMISMATCH_ER:
        return prefix + "arguments number mismatch for '" + additional_info_ + "'";
    case FOPEN_ER:
        return "error: can't open file";
    }
    return "No errors occured";
}
