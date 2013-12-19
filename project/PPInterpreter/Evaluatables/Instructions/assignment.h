#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Evaluatables/evaluatable.h"

class Assignment : public Evaluatable {
  public:
    Assignment(std::string id, PtrEval expr) : id_(id), expr_(expr) {}
    int Evaluate(Scope &scope, Error& error);

  private:
    std::string id_;
    PtrEval expr_;
};

#endif // ASSIGNMENT_H
