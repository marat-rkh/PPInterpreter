#ifndef FUNCCALLCREATOR_H
#define FUNCCALLCREATOR_H

#include <string>
#include <vector>

#include "Visitables/expr.h"
#include "Visitables/funccall.h"

class FuncCallCreator {
public:
    FuncCallCreator() {}
    void SetIDAndLine(std::string id, size_t line_num) {
        id_ = id;
        line_number_ = line_num;
    }
    void AddParam(Expr const& expr) { params_.push_back(expr); }
    FuncCall Create() { return FuncCall(id_, params_, line_number_); }

private:
    std::string id_;
    size_t line_number_;
    std::vector<Expr> params_;
};

#endif // FUNCCALLCREATOR_H
