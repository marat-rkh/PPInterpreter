#include "assignment.h"
#include "Evaluatables/function.h"
#include "Evaluatables/evaluatable.h"
#include "returninstr.h"
#include "Evaluatables/number.h"

int Assignment::Evaluate(Scope &scope, Error& error) {
    int value = expr_->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    Scope::iterator it = scope.find(id_);

    PtrEval number_expr(new Number(value));
    InstructionBlock body;
    body.AddInstruction(number_expr);
    PtrEval func(new Function(body, std::vector<std::string>()));

    if(it == scope.end()) {
        scope.insert(std::pair<std::string, PtrEval>(id_, func)); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else {
        it->second = func; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    return 0;
}
