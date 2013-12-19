#ifndef FUNCCALLCREATOR_H
#define FUNCCALLCREATOR_H

#include <string>
#include <vector>

#include "expr.h"
#include "funccall.h"

class FuncCallCreator {
public:
    FuncCallCreator();
    void SetID(std::string id) { id_ = id; }
    void AddParam(Expr const& expr) { params_.push_back(expr); }
    FuncCall Create() { return FuncCall(id_, params_); }

private:
    std::string id_;
    std::vector<Expr> params_;
};

#endif // FUNCCALLCREATOR_H
