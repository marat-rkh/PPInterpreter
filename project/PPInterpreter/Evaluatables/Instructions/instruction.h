#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Evaluatables/evaluatable.h"
#include "Evaluatables/instructionblock.h"

#include <memory>

//unused class

class Instruction : public Evaluatable {
//  public:
//    Instruction(InstructionBlock& parent): parent_(parent) {}
////    virtual bool IsReturnInstruction() = 0;
//    InstructionBlock& parent_;
};

//typedef std::shared_ptr<Instruction> PtrInstr;

#endif // INSTRUCTION_H
