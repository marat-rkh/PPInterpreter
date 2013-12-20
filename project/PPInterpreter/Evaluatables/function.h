#ifndef FUNCTION_H
#define FUNCTION_H

#include "visitable.h"
#include "Evaluator/visitor.h"
#include "instructionblock.h"

#include <vector>

class Function : public Visitable {
  public:
    Function() : params_(), body_(), local_scope_() {}
    Function(InstructionBlock const& instr_block, std::vector<std::string> const& params):
        params_(params),
        body_(instr_block),
        local_scope_()
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
    Scope local_scope_;
};

#endif // FUNCTION_H
