#ifndef EVALUATABLE_H
#define EVALUATABLE_H

#include "params.h"

#include <cstddef>
#include <map>
#include <string>
#include <memory>

class Evaluatable;

typedef std::shared_ptr<Evaluatable> PtrEval;
typedef std::map<std::string, PtrEval> Scope;

class Evaluatable {
public:
    enum ErrorType {SYNTAX_ER, DIVBYZERO_ER, UNDEFVAR_ER, UNDEFFUNC_ER, ARGNUMMISMATCH_ER, NOERRORS};

    Evaluatable(): line_number_(0), last_error_type_(NOERRORS) {}
    void SetErrorFlag(ErrorType error_type);
    ErrorType GetErrorType() { return last_error_type_; }
    void SetLineNumber(size_t line) { line_number_ = line; }
    size_t GetLineNumber() { return line_number_; }
    bool ErrorOccured() { return last_error_type_ == NOERRORS; }

    virtual int Evaluate(Scope& scope, Params const& params) = 0;

protected:
    size_t line_number_;
    ErrorType last_error_type_;
};

#endif // EVALUATABLE_H
