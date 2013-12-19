#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

#include "Evaluatables/evaluatable.h"
#include "Evaluatables/instructionblock.h"
#include "globalscope.h"

using std::vector;
using std::map;
using std::string;

class Program {
  public:
    Program() {}
    Program(InstructionBlock const& ib): body_(ib), variables_() {}
    Program(Program const& pr): body_(pr.body_), variables_(pr.variables_) {}
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    int Evaluate(Error& error) {
        body_.Evaluate(variables_, error);
        return 0;
    }
  private:
    InstructionBlock body_;
    Scope variables_;
};

#endif // PROGRAM_H
