#ifndef TERM_H
#define TERM_H

#include "arithmexpr.h"

class Term : public ArithmExpr {
public:
    Term();
    int Evaluate(Scope &scope, const Params &params);
};

#endif // TERM_H
