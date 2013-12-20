#ifndef GLOBALSCOPE_H
#define GLOBALSCOPE_H

#include "defines.h"
#include "function.h"

typedef std::shared_ptr<Function> PtrFunc;
typedef std::map<std::string, PtrFunc> GSFuncs;

class GlobalScope {
public:
    static GlobalScope& GetInstance() {
        static GlobalScope global_scope;
        return global_scope;
    }
    GSFuncs gs_funcs;

private:
    GlobalScope(): gs_funcs() {}
    DISABLE_COPY_AND_ASSIGN(GlobalScope);
};

#endif // GLOBALSCOPE_H
