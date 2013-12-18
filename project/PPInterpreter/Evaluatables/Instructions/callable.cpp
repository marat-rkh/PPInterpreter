#include "callable.h"

#include <string>
#include <map>

#include "function.h"

using std::map;
using std::string;

int Callable::Evaluate(Scope& scope, Error &error) {
    Scope::iterator it = scope.find(id_);
    if(it == scope.end()) {
        error.Set(Error::UNDEFVAR_ER, line_number_);
        return 0;
    }
    int value = (it->second)->Evaluate(scope, error);
    if(error.IsOccured()) {
        return 0;
    }
    return value;
}
