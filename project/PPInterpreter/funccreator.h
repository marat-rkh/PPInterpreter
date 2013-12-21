#ifndef FUNCCREATOR_H
#define FUNCCREATOR_H

#include <string>

#include "instructionblock.h"
#include "globalscope.h"
#include "function.h"

class FuncCreator {
  public:
    FuncCreator() {}
    void SetIDAndLine(std::string id, size_t line_num) {
        id_ = id;
        line_number_ = line_num;
    }
    void AddParam(std::string param_name) { params_.push_back(param_name); }
    void CreateWithBody(InstructionBlock const& body) {
        PtrFunc func(new Function(body, params_, line_number_));
        GlobalScope::GetInstance().gs_funcs.insert(std::pair<std::string, PtrFunc> (id_, func));
    }

  private:
    std::string id_;
    size_t line_number_;
    std::vector<std::string> params_;
};

#endif // FUNCCREATOR_H
