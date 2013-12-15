#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

#include "evaluatable.h"
#include "instruction.h"

using std::vector;
using std::map;
using std::string;

class Program : public Evaluatable {
public:
    Program();
    void AddInstr(PtrInstr instr) { instructions_.push_back(instr); }
    void AddFunc(std::string id, PtrEval func) {
        functions_.insert(std::pair<std::string, PtrEval>(id, func));
    }
    int Evaluate(Scope &scope, const Params &params);

private:
    std::vector<PtrInstr> instructions_;
    Scope functions_;
};

#endif // PROGRAM_H
