#ifndef EXPR_H
#define EXPR_H

#include "arithmexpr.h"

class Expr : public ArithmExpr {
public:
    Expr() {}
    Expr(Expr const& e):
        operations_(e.operations_),
        elements_(e.elements_),
        line_number_(e.line_number_)
    {}

    int Evaluate(Scope &scope, Error& error);
};

#endif // EXPR_H
