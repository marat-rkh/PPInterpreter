#ifndef EXPR_H
#define EXPR_H

#include "arithmexpr.h"
#include "term.h"

class Expr : public ArithmExpr {
public:
    Expr() {}
    Expr(Expr const& e): ArithmExpr(e) {}
    void AddTerm(Term const& t) {
        elements_.push_back(PtrVisitable(new Term(t)));
    }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

#endif // EXPR_H
