#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "evaluatable.h"

#include <memory>

class Instruction : public Evaluatable {
  public:
    virtual bool IsReturnInstruction() = 0;
};

typedef std::shared_ptr<Instruction> PtrInstr;

#endif // INSTRUCTION_H
