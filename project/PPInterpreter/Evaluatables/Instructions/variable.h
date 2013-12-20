#ifndef VARIABLE_H
#define VARIABLE_H

#include "visitable.h"
#include "Evaluator/visitor.h"

class Variable : public Visitable {
  public:
    Variable(std::string id): id_(id) {}
    std::string& id() { return id_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
};

#endif // VARIABLE_H
