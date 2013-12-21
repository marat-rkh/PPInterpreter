#ifndef CONDITION_H
#define CONDITION_H

#include "visitable.h"
#include "expr.h"

class Condition : public Visitable {
  public:
    Condition() {}
    Condition(Expr e1, Expr e2, std::string comp_char):
        Visitable(),
        e1_(e1),
        e2_(e2),
        comp_char_(comp_char)
    {}
    Condition(Condition const& c):
        Visitable(c),
        e1_(c.e1_),
        e2_(c.e2_),
        comp_char_(c.comp_char_)
    {}

    Expr& e1() { return e1_; }
    Expr& e2() { return e2_; }
    std::string& comp_char() { return comp_char_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    Expr e1_;
    Expr e2_;
    std::string comp_char_;
};

#endif // CONDITION_H
