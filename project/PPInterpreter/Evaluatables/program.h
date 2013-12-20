#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

#include "visitable.h"
#include "Evaluator/visitor.h"
#include "Evaluatables/instructionblock.h"
#include "globalscope.h"

using std::vector;
using std::map;
using std::string;

class Program: public Visitable {
  public:
    Program() {}
    Program(InstructionBlock const& ib): body_(ib), error_() {}
    Program(Program const& pr):
        Visitable(pr),
        body_(pr.body_),
        error_()
    {}
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    InstructionBlock& body() { return body_; }
    void SetError(Error e) { error_.Set(e.GetErrorType(), e.last_error_line()); }
    bool RuntimeErrorIsOccured() { return error_.GetErrorType() != Error::NOERRORS; }
    std::string GetErrorMessage() { return error_.GetErrorMessage(); }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    InstructionBlock body_;
    Error error_;
};

#endif // PROGRAM_H