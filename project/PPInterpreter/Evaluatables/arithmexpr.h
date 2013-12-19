#ifndef ARITHMEXPR_H
#define ARITHMEXPR_H

#include "evaluatable.h"

#include <vector>

class ArithmExpr : public Evaluatable {
  public:
    ArithmExpr() {}
    ArithmExpr(ArithmExpr const& ae):
        Evaluatable(ae),
        operations_(ae.operations_),
        elements_(ae.elements_)
    {}
    void AddOperation(std::string operation) { operations_.push_back(operation); }
    void AddElem(PtrEval elem) { elements_.push_back(elem); }
    int Evaluate(Scope &scope, Error& error) = 0;

  protected:
    std::vector<std::string> operations_;
    std::vector<PtrEval> elements_;
};

#endif // ARITHMEXPR_H
