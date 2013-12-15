#ifndef EXPR_H
#define EXPR_H

#include "arithmexpr.h"

class Expr : public ArithmExpr {
public:
    Expr();
    int Evaluate(Scope &scope, const Params &params);
};

#endif // EXPR_H
