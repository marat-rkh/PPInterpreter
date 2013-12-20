#ifndef VISITABLE_H
#define VISITABLE_H

#include <cstddef>
#include <map>
#include <string>
#include <memory>

#include "error.h"

class Visitor;
class Visitable;

typedef std::shared_ptr<Visitable> PtrVisitable;
typedef std::map<std::string, PtrVisitable> Scope;

class Visitable {
public:
    Visitable(): line_number_(0) {}
    Visitable(Visitable const& e): line_number_(e.line_number_) {}
    void SetLineNumber(size_t line) { line_number_ = line; }
    size_t line_number() { return line_number_; }

    virtual int accept(Visitor &v) = 0;

protected:
    size_t line_number_;
};

#endif // VISITABLE_H
