#ifndef CALLABLE_H
#define CALLABLE_H

#include "evaluatable.h"

#include <string>

class Callable : public Evaluatable {
public:
    Callable(std::string id): id_(id) {}
    int Evaluate(Scope& scope, const Params &params);
private:
    std::string id_;
};

#endif // CALLABLE_H
