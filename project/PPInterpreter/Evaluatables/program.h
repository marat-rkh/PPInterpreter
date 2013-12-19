#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

#include "Evaluatables/evaluatable.h"
#include "Evaluatables/instructionblock.h"
#include "globalscope.h"

using std::vector;
using std::map;
using std::string;

class Program : public Evaluatable {
  public:
    Program(): body_(), variables_() {}
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    int Evaluate(Scope &scope, Error& error) {
        body_.Evaluate(scope, error);
        return 0;
    }
  private:
    InstructionBlock body_;
    Scope variables_;
};

#endif // PROGRAM_H
