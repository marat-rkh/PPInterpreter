#ifndef READINSTR_H
#define READINSTR_H

#include "visitable.h"
#include "Evaluator/visitor.h"

class ReadInstr : public Visitable {
public:
    ReadInstr(std::string id): id_(id) {}
    ReadInstr(ReadInstr const& ri):
        Visitable(ri),
        id_(ri.id_) {}
    std::string& id() { return id_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    std::string id_;
};

#endif // READINSTR_H
