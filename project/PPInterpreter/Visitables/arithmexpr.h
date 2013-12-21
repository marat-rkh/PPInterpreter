#ifndef ARITHMEXPR_H
#define ARITHMEXPR_H

#include "visitable.h"
#include "../visitor.h"

#include <vector>

class ArithmExpr : public Visitable {
  public:
    ArithmExpr() {}
    ArithmExpr(ArithmExpr const& ae):
        Visitable(ae),
        operations_(ae.operations_),
        elements_(ae.elements_)
    {}
    void AddOperation(std::string operation) { operations_.push_back(operation); }
    void AddElem(PtrVisitable elem) { elements_.push_back(elem); }

    std::vector<std::string>& operations() { return operations_; }
    std::vector<PtrVisitable>& elements() { return elements_; }

    int accept(Visitor &v) = 0;

  protected:
    std::vector<std::string> operations_;
    std::vector<PtrVisitable> elements_;
};

#endif // ARITHMEXPR_H
