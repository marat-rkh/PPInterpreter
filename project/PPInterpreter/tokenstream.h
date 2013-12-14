#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include <vector>
#include <string>

#include "token.h"

#define DISABLE_COPY_AND_ASSIGN(TypeName) \
    TypeName(TypeName const&); \
    void operator=(TypeName const&)

using std::vector;
using std::string;

class TokenStream {
public:
    TokenStream(vector<Token> const& tokens):
        tokens_(tokens),
        current_pos_(-1),
        fixed_pos_(-1)
    {}
    bool NextTokenTypeEqualsTo(TokenType type) {
        return tokens_[++current_pos_].type_ == type;
    }
    bool NextTokenValueEqualsTo(string value) {
        return tokens_[++current_pos_].value_ == value;
    }
    bool CurrentTokenTypeEqualsTo(TokenType type) {
        return tokens_[current_pos_].type_ == type;
    }
    bool CurrentTokenValueEqualsTo(string value) {
        return tokens_[current_pos_].value_ == value;
    }
    bool End() {
        return current_pos_ == static_cast<int>(tokens_.size() - 1);
    }
    bool CompareTypeWithRollback(TokenType type);
    bool CompareValueWithRollback(string value);

    void FixPosition() { fixed_pos_ = current_pos_; }
    void RollbackToFixedPosition() { current_pos_ = fixed_pos_; }

    string val() {
        return tokens_[current_pos_].value_;
    }

private:
    DISABLE_COPY_AND_ASSIGN(TokenStream);

    vector<Token> tokens_;
    int current_pos_;
    int fixed_pos_;
};

#endif // TOKENSTREAM_H
