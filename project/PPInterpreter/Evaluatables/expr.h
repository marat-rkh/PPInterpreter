#ifndef EXPR_H
#define EXPR_H

#include "arithmexpr.h"
#include "term.h"

class Expr : public ArithmExpr {
public:
    Expr() {}
    Expr(Expr const& e): ArithmExpr(e) {}
    void AddTerm(Term const& t) {
        elements_.push_back(PtrEval(new Term(t)));
    }

    int Evaluate(Scope &scope, Error& error);
};

#endif // EXPR_H
