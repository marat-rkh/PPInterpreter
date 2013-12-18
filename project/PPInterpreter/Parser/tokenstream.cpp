#include "tokenstream.h"

bool TokenStream::CompareTypeWithRollback(TokenType type) {
    if(!NextTokenTypeEqualsTo(type)) {
        --current_pos_;
        return false;
    }
    return true;
}

bool TokenStream::CompareValueWithRollback(string value) {
    if(!NextTokenValueEqualsTo(value)) {
        --current_pos_;
        return false;
    }
    return true;
}
