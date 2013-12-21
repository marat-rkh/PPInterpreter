#include "tokenstream.h"

bool TokenStream::LookaheadType(TokenType type) {
    if(!NextTokenTypeEqualsTo(type)) {
        --current_pos_;
        return false;
    }
    return true;
}

bool TokenStream::LookaheadValue(string value) {
    if(!NextTokenValueEqualsTo(value)) {
        --current_pos_;
        return false;
    }
    return true;
}
