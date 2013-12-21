#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "visitable.h"
#include "Evaluator/visitor.h"

class Assignment : public Visitable {
  public:
    Assignment(std::string id, PtrVisitable expr, size_t line_num):
        Visitable(line_num),
        id_(id),
        expr_(expr)
    {}
    Assignment(Assignment const& assign):
        Visitable(assign),
        id_(assign.id_),
        expr_(assign.expr_)
    {}
    std::string& id() { return id_; }
    PtrVisitable& expr() { return expr_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
    PtrVisitable expr_;
};

#endif // ASSIGNMENT_H
