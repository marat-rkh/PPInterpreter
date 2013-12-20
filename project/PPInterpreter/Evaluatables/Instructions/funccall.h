#ifndef FUNCCALL_H
#define FUNCCALL_H

#include <vector>

#include "visitable.h"
#include "Evaluator/visitor.h"
#include "expr.h"

class FuncCall : public Visitable {
  public:
    FuncCall(std::string& id, std::vector<Expr>& params, size_t line_num):
        Visitable(line_num),
        id_(id),
        params_(params)
    {}
    FuncCall(FuncCall const& fc):
        Visitable(fc),
        id_(fc.id_),
        params_(fc.params_)
    {}
    std::string& id() { return id_; }
    std::vector<Expr>& params() { return params_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
    std::vector<Expr> params_;
};

#endif // FUNCCALL_H
