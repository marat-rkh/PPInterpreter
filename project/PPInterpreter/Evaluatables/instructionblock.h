#ifndef INSTRUCTIONBLOCK_H
#define INSTRUCTIONBLOCK_H

#include <vector>

#include "visitable.h"
#include "Evaluator/visitor.h"

class InstructionBlock : public Visitable {
  public:
    InstructionBlock(): Visitable(){}
    InstructionBlock(PtrVisitable const& instr) {
        AddInstruction(instr);
    }
    InstructionBlock(InstructionBlock const& instr_block):
        Visitable(instr_block),
        instructions_(instr_block.instructions_)
    {}
    void AddInstruction(PtrVisitable instr) {
        instructions_.push_back(instr);
    }
    void operator=(InstructionBlock const& instr_block) {
        instructions_ = instr_block.instructions_;
    }
    std::vector<PtrVisitable>& instructions() { return instructions_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::vector<PtrVisitable> instructions_;
};

#endif // INSTRUCTIONBLOCK_H
