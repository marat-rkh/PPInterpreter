#ifndef TERM_H
#define TERM_H

#include "arithmexpr.h"

class Term : public ArithmExpr {
public:
    Term() {}
    Term(Term const& t): ArithmExpr(t) {}
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

#endif // TERM_H
