#ifndef NUMBER_H
#define NUMBER_H

#include "visitable.h"
#include "Evaluator/visitor.h"

#include <cstdlib>

class Number : public Visitable {
public:
    Number(int val): value_(val) {}
    Number(std::string const& num) { value_ = atoi(num.c_str()); }
    int value() { return value_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    int value_;
};

#endif // NUMBER_H
