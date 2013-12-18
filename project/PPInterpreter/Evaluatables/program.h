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
    Program();
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    void AddFunc(std::string id, PtrEval func) {
        GlobalScope.GetInstance().scope_map.insert(std::pair<std::string, PtrEval>(id, func));
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
