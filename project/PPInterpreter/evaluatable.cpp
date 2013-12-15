#include "evaluatable.h"

void Evaluatable::SetErrorFlag(ErrorType error_type) {
    if(last_error_type_ == NOERRORS) {
        last_error_type_ = error_type;
    }
}
