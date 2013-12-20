#ifndef FUNCCREATOR_H
#define FUNCCREATOR_H

#include <string>

#include "instructionblock.h"
#include "globalscope.h"
#include "function.h"

class FuncCreator {
  public:
    FuncCreator() {}
    void SetID(std::string id) { id_ = id; }
    void AddParam(std::string param_name) { params_.push_back(param_name); }
    void CreateWithBody(InstructionBlock const& body) {
        PtrFunc func(new Function(body, params_));
        GlobalScope::GetInstance().gs_funcs.insert(std::pair<std::string, PtrFunc> (id_, func));
// check multiple function declaration!
    }

  private:
    std::string id_;
    std::vector<std::string> params_;
};

#endif // FUNCCREATOR_H
