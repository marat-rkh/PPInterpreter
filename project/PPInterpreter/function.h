#ifndef FUNCTION_H
#define FUNCTION_H

#include "evaluatable.h"
#include "instruction.h"

#include <vector>

class Function : public Evaluatable {
  public:
    Function() : params_num_(0) {}
    Function(PtrInstr instr) : params_num_(0) { AddInstruction(instr); }
//    void AddParam(std::string param_name) { params_.push_back(param_name); }
    void IncrParamsNumber() { ++params_num_; }
    void AddInstruction(PtrInstr instr) { instructions_.push_back(instr); }
    int Evaluate(Scope &scope, const Params &params);

  private:
//    std::vector<std::string> params_;
    size_t params_num_;
    std::vector<PtrInstr> instructions_;
    Scope local_scope_;
};

#endif // FUNCTION_H
