#ifndef FACTOR_H
#define FACTOR_H

#include "visitable.h"
#include "../visitor.h"

class Factor : public Visitable {
public:
    Factor() {}
    Factor(Factor const& f):
        Visitable(f),
        unary_operator_(f.unary_operator_),
        fact_expr_(f.fact_expr_)
    {}
    void SetFactExpr(PtrVisitable const& fact_expr) {
        fact_expr_ = fact_expr;
    }
    void SetUnaryOperator(std::string const& uo) { unary_operator_ = uo; }
    std::string const& unary_operator() { return unary_operator_; }
    PtrVisitable const& fact_expr() { return fact_expr_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    std::string unary_operator_;
    PtrVisitable fact_expr_;
};

#endif // FACTOR_H
