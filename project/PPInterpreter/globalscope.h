#ifndef GLOBALSCOPE_H
#define GLOBALSCOPE_H

#include "Evaluatables/evaluatable.h"

#define DISABLE_COPY_AND_ASSIGN(Type) \
    Type(Type const&); \
    void operator=(Type const&)

class GlobalScope {
public:
    static GlobalScope& GetInstance() {
        static GlobalScope global_scope;
        return global_scope;
    }
    Scope scope_map;

private:
    GlobalScope(): scope_map() {}
    DISABLE_COPY_AND_ASSIGN(GlobalScope);
};

#endif // GLOBALSCOPE_H
