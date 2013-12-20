#ifndef INSTRUCTIONBLOCK_H
#define INSTRUCTIONBLOCK_H

#include <vector>

#include "Evaluatables/evaluatable.h"

class InstructionBlock : public Evaluatable {
  public:
    InstructionBlock():  Evaluatable(), has_returned_(false) {}
    InstructionBlock(PtrEval const& instr): has_returned_(false) {
        AddInstruction(instr);
    }
    InstructionBlock(InstructionBlock const& instr_block):
        Evaluatable(instr_block),
        has_returned_(false),
        instructions_(instr_block.instructions_)
    {}
    void AddInstruction(PtrEval instr) {
        instructions_.push_back(instr);
    }
    void operator=(InstructionBlock const& instr_block) {
        instructions_ = instr_block.instructions_;
    }
    int Evaluate(Scope &scope, Error& error);

    bool has_returned_;

  private:
    std::vector<PtrEval> instructions_;
};

#endif // INSTRUCTIONBLOCK_H
