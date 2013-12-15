#ifndef ARITHMEXPR_H
#define ARITHMEXPR_H

#include "evaluatable.h"

#include <vector>

class ArithmExpr : public Evaluatable {
public:
    ArithmExpr();
    void AddOperation(std::string operation) { operations_.push_back(operation); }
    void AddElem(PtrEval elem) { elements_.push_back(elem); }
    int Evaluate(Scope &scope, const Params &params) = 0;

protected:
    std::vector<std::string> operations_;
    std::vector<PtrEval> elements_;
};

#endif // ARITHMEXPR_H
