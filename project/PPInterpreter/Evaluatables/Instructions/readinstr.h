#ifndef READINSTR_H
#define READINSTR_H

#include "evaluatable.h"

class ReadInstr : public Evaluatable {
public:
    ReadInstr(std::string id): id_(id) {}
    ReadInstr(ReadInstr const& ri):
        Evaluatable(ri),
        id_(ri.id_) {}
    int Evaluate(Scope &scope, Error &error);

private:
    std::string id_;
};

#endif // READINSTR_H
