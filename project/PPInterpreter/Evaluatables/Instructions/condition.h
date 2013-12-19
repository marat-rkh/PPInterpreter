#ifndef CONDITION_H
#define CONDITION_H

#include "Evaluatables/evaluatable.h"
#include "Evaluatables/expr.h"

class Condition : public Evaluatable {
  public:
    Condition(Expr e1, Expr e2, std::string comp_char):
        e1_(e1),
        e2_(e2),
        comp_char_(comp_char)
    {}
    Condition(Condition const& c):
        Evaluatable(c),
        e1_(c.e1_),
        e2_(c.e2_),
        comp_char_(c.comp_char_)
    {}
    int Evaluate(Scope &scope, Error &error);

  private:
    Expr e1_;
    Expr e2_;
    std::string comp_char_;
};

#endif // CONDITION_H
