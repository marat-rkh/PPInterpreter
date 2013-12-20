#ifndef VARIABLE_H
#define VARIABLE_H

#include "evaluatable.h"

class Variable : public Evaluatable {
  public:
    Variable(std::string id): id_(id) {}
    int Evaluate(Scope& scope, Error& error);

  private:
    std::string id_;
};

#endif // VARIABLE_H
