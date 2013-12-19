#ifndef EXPR_H
#define EXPR_H

#include "arithmexpr.h"

class Expr : public ArithmExpr {
public:
    Expr() {}
    Expr(Expr const& e): ArithmExpr(e) {}

    int Evaluate(Scope &scope, Error& error);
};

#endif // EXPR_H
