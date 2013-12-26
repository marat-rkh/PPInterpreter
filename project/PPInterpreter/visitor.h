#ifndef VISITOR_H
#define VISITOR_H

class Program;
class Function;
class InstructionBlock;
class ReadInstr;
class PrintInstr;
class ReturnInstr;
class Assignment;
class FuncCall;
class Variable;
class ArithmExpr;
class Factor;
class Number;
class Condition;
class IfInstr;
class WhileInstr;

class Visitor {
public:
    Visitor() {}
    virtual int visit(Program *c) = 0;
    virtual int visit(Function *c) = 0;
    virtual int visit(InstructionBlock *c) = 0;
    virtual int visit(ReadInstr *c) = 0;
    virtual int visit(PrintInstr *c) = 0;
    virtual int visit(ReturnInstr *c) = 0;
    virtual int visit(Assignment *c) = 0;
    virtual int visit(FuncCall *c) = 0;
    virtual int visit(Variable *c) = 0;
    virtual int visit(ArithmExpr *c) = 0;
    virtual int visit(Factor *c) = 0;
    virtual int visit(Number *c) = 0;
    virtual int visit(Condition *c) = 0;
    virtual int visit(IfInstr *c) = 0;
    virtual int visit(WhileInstr *c) = 0;
};

#endif // VISITOR_H
