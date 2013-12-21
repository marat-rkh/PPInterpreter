#ifndef FUNCTION_H
#define FUNCTION_H

#include "visitable.h"
#include "../visitor.h"
#include "instructionblock.h"

#include <vector>

class Function : public Visitable {
  public:
    Function() : params_(), body_() {}
    Function(InstructionBlock const& instr_block, std::vector<std::string> const& params, size_t line_num):
        Visitable(line_num),
        params_(params),
        body_(instr_block)
    {}
    void AddParam(std::string param_name) {
        params_.push_back(param_name);
    }
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    std::vector<std::string>& params() { return params_; }
    InstructionBlock& body() { return body_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::vector<std::string> params_;
    InstructionBlock body_;
};

#endif // FUNCTION_H
