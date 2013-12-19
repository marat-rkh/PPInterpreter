#ifndef FUNCCALL_H
#define FUNCCALL_H

#include <vector>

#include "callable.h"
#include "expr.h"

class FuncCall : public Evaluatable {
  public:
    FuncCall(std::string& id, std::vector<Expr>& params):
        id_(id),
        params_(params)
    {}
    int Evaluate(Scope &scope, Error &error);

  private:
    std::string id_;
    std::vector<Expr> params_;
};

#endif // FUNCCALL_H
