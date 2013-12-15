#include "assignment.h"
#include "function.h"
#include "number.h"
#include "returninstr.h"

int Assignment::Evaluate(Scope &scope, const Params &params) {
    int value = expr_->Evaluate(scope, params);
    if(expr_->ErrorOccured()) {
        SetErrorFlag(expr_->GetErrorType());
        SetLineNumber(expr_->GetLineNumber());
        return 0;
    }
    Scope::iterator it = scope.find(id_);

    PtrEval number_expr(new Number(value));
    PtrInstr return_instr(new ReturnInstr(number_expr));
    PtrEval func(new Function(return_instr));

    if(it == scope.end()) {
        scope.insert(std::pair<std::string, PtrEval>(id_, func)); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else {
        it->second = func; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    return 0;
}
