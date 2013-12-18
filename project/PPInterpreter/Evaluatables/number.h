#ifndef NUMBER_H
#define NUMBER_H

#include "evaluatable.h"

class Number : public Evaluatable {
public:
    Number(int val): value_(val) {}
    Number(std::string const& num);
    int Evaluate(Scope &scope, Error& error);

private:
    int value_;
};

#endif // NUMBER_H
