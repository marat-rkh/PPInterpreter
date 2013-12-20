#include "funccall.h"
#include "globalscope.h"
#include "number.h"
#include "function.h"

int FuncCall::Evaluate(Scope &scope, Error &error) {
    GSFuncs::iterator it = GlobalScope::GetInstance().gs_funcs.find(id_);
    if(it == GlobalScope::GetInstance().gs_funcs.end()) {
        error.Set(Error::UNDEFFUNC_ER, line_number_);
        return 0;
    }
    std::vector<std::string> params_names((it->second)->GetParams());
    if(params_names.size() != params_.size()) {
        error.Set(Error::ARGNUMMISMATCH_ER, line_number_);
        return 0;
    }
    Scope local_scope;
    for(size_t i = 0; i != params_.size(); ++i) {
        int value = params_[i].Evaluate(scope, error);
        if(error.IsOccured()) {
            return 0;
        }
        PtrEval number(new Number(value));
        local_scope.insert(std::pair<std::string, PtrEval>(params_names[i], number));
    }
    int value = (it->second)->Evaluate(local_scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    return value;
}
