#ifndef EVALUATABLE_H
#define EVALUATABLE_H

#include <cstddef>
#include <map>
#include <string>
#include <memory>

#include "error.h"

class Evaluatable;

typedef std::shared_ptr<Evaluatable> PtrEval;
typedef std::map<std::string, PtrEval> Scope;

class Evaluatable {
public:
    Evaluatable(): line_number_(0) {}
    Evaluatable(Evaluatable const& e): line_number_(e.line_number_) {}
    void SetLineNumber(size_t line) { line_number_ = line; }
    size_t GetLineNumber() { return line_number_; }

    virtual int Evaluate(Scope& scope, Error& error) = 0;

protected:
    size_t line_number_;
};

#endif // EVALUATABLE_H
