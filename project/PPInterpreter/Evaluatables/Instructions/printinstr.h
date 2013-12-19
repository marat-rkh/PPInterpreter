#ifndef PRINTINSTR_H
#define PRINTINSTR_H

#include "Evaluatables/evaluatable.h"

class PrintInstr : public Evaluatable {
  public:
    PrintInstr(PtrEval expr) : expr_(expr) {}
    int Evaluate(Scope &scope, Error &error);

  private:
    PtrEval expr_;
};

#endif // PRINTINSTR_H
