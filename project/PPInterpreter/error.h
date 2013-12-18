#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>

class Error {
public:
    enum ErrorType {SYNTAX_ER, DIVBYZERO_ER, UNDEFVAR_ER, UNDEFFUNC_ER, ARGNUMMISMATCH_ER, NOERRORS};

    Error() : last_error_type_(NOERRORS), last_error_line_(0) {}
    bool IsOccured() { return last_error_type_ != NOERRORS; }
    ErrorType GetErrorType() { return last_error_type_; }
    void Set(ErrorType error_type, size_t line_number) {
        if(last_error_type_ == NOERRORS) {
            last_error_type_ = error_type;
            last_error_line_ = line_number;
        }
    }

private:
    ErrorType last_error_type_;
    size_t last_error_line_;
};

#endif // ERROR_H
