#include "assignment.h"
#include "Evaluatables/function.h"
#include "number.h"
#include "Instructions/returninstr.h"

int Assignment::Evaluate(Scope &scope, Error& error) {
    int value = expr_->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    Scope::iterator it = scope.find(id_);

    PtrEval number_expr(new Number(value));
    PtrInstr return_instr(new ReturnInstr(number_expr));
    InstructionBlock body(return_instr);
    PtrEval func(new Function(body));

    if(it == scope.end()) {
        scope.insert(std::pair<std::string, PtrEval>(id_, func)); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else {
        it->second = func; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    return 0;
}
