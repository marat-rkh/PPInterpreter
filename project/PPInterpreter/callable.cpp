#include "callable.h"

#include <string>
#include <map>

#include "function.h"

using std::map;
using std::string;

int Callable::Evaluate(Scope& scope, const Params &params) {
    Scope::iterator it = scope.find(id_);
    if(it == scope.end()) {
        SetErrorFlag(UNDEFVAR_ER);
        return 0;
    }
    int value = (it->second)->Evaluate(scope, params);
    if((it->second)->ErrorOccured()) {
        SetErrorFlag((it->second)->GetErrorType());
        SetLineNumber((it->second)->GetLineNumber());
        return 0;
    }
    return value;
}
