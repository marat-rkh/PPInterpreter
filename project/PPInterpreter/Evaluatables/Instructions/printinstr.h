#ifndef PRINTINSTR_H
#define PRINTINSTR_H

#include "visitable.h"
#include "Evaluator/visitor.h"
#include "expr.h"

class PrintInstr : public Visitable {
  public:
    PrintInstr(): expr_() {}
    PrintInstr(PtrVisitable expr) : expr_(expr) {}
    PrintInstr(Expr const& expr): expr_(PtrVisitable(new Expr(expr))) {}
    void SetExpr(Expr const& expr) {
        expr_ = PtrVisitable(new Expr(expr));
    }
    PtrVisitable& expr() { return expr_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    PtrVisitable expr_;
};

#endif // PRINTINSTR_H
