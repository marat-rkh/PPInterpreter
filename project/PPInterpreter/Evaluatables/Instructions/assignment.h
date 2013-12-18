#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Instructions/instruction.h"

class Assignment : public Instruction {
  public:
    Assignment(std::string id, PtrEval expr) : id_(id), expr_(expr) {}
    int Evaluate(Scope &scope, Error& error);

  private:
    std::string id_;
    PtrEval expr_;
};

#endif // ASSIGNMENT_H
