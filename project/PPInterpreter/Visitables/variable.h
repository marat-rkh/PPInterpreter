#ifndef VARIABLE_H
#define VARIABLE_H

#include "visitable.h"
#include "../visitor.h"

class Variable : public Visitable {
  public:
    Variable(std::string id, size_t line_num):
        Visitable(line_num),
        id_(id)
    {}
    std::string& id() { return id_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
};

#endif // VARIABLE_H
