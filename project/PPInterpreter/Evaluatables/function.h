#ifndef FUNCTION_H
#define FUNCTION_H

#include "evaluatable.h"
#include "instructionblock.h"

#include <vector>

class Function : public Evaluatable {
  public:
    Function() : params_num_(0), body_() {}
    Function(InstructionBlock const& instr_block): params_num_(0), body_(instr_block) {}
    void IncrParamsNumber() {
        ++params_num_;
    }
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    int Evaluate(Scope &scope, Error& error);

  private:
    size_t params_num_;
    InstructionBlock body_;
    Scope local_scope_;
};

#endif // FUNCTION_H
