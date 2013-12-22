#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>
#include <string>

class Error {
public:
    enum ErrorType {DIVBYZERO_ER, UNDEFVAR_ER, UNDEFFUNC_ER, ARGNUMMISMATCH_ER, NOERRORS};
    Error() :
        last_error_type_(NOERRORS),
        last_error_line_(0)
    {}
    bool IsOccured() { return last_error_type_ != NOERRORS; }
    void Set(ErrorType error_type, size_t line_number);
    void Set(ErrorType error_type, size_t line_number, std::string add_info);
    std::string GetErrorMessage();
    ErrorType const& last_error_type() { return last_error_type_; }
    size_t last_error_line() { return last_error_line_; }
    std::string const& additional_info() { return additional_info_; }

private:
    ErrorType last_error_type_;
    size_t last_error_line_;
    std::string additional_info_;
};

#endif // ERROR_H
