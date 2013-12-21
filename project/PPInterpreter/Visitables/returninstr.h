#ifndef RETURNINSTR_H
#define RETURNINSTR_H

#include "visitable.h"
#include "../visitor.h"
#include "instructionblock.h"
#include <iostream>

class ReturnInstr : public Visitable {
  public:
    ReturnInstr(PtrVisitable expr) : expr_(expr) {}
    ReturnInstr(ReturnInstr const& ri):
        Visitable(ri),
        expr_(ri.expr_)
    {}
    PtrVisitable& expr() { return expr_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    PtrVisitable expr_;
};

#endif // RETURNINSTR_H
