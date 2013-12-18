#include "instructionblock.h"

int InstructionBlock::Evaluate(Scope &scope, Error& error) {
    for(size_t i = 0; i != instructions_.size(); ++i) {
        int value = instructions_[i]->Evaluate(scope, error);
        if(error.IsOccured()) {
            return 0;
        }
        if(has_returned_) {
            return value;
        }
    }
    return 0;
}
