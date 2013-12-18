#ifndef TERM_H
#define TERM_H

#include "arithmexpr.h"

class Term : public ArithmExpr {
public:
    Term();
    int Evaluate(Scope &scope, Error& error);
};

#endif // TERM_H
