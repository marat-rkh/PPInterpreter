#ifndef PRINTINSTR_H
#define PRINTINSTR_H

#include "Evaluatables/evaluatable.h"
#include "expr.h"

class PrintInstr : public Evaluatable {
  public:
    PrintInstr(): expr_() {}
    PrintInstr(PtrEval expr) : expr_(expr) {}
    PrintInstr(Expr const& expr): expr_(PtrEval(new Expr(expr))) {}
    void SetExpr(Expr const& expr) {
        expr_ = PtrEval(new Expr(expr));
    }

    int Evaluate(Scope &scope, Error &error);

  private:
    PtrEval expr_;
};

#endif // PRINTINSTR_H
