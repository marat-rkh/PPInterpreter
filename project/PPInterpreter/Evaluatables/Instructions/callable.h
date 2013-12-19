#ifndef CALLABLE_H
#define CALLABLE_H

#include "Evaluatables/evaluatable.h"

#include <string>

class Callable : public Evaluatable {
  public:
    Callable() {}
//    PtrEval TryFindEvaluatable(Scope& scope, std::string id) {
//        Scope::iterator it = scope.find(id);
//        return it == scope.end() ? 0 : it->second;
//    }
//    int Evaluate(Scope& scope, Error& error) = 0;
};

#endif // CALLABLE_H
