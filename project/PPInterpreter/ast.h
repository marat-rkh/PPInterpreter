#ifndef AST_H
#define AST_H

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "visitor.h"
#include "error.h"

class Visitor;
class Visitable;

typedef std::shared_ptr<Visitable> PtrVisitable;

class Visitable {
public:
    Visitable(): line_number_(0) {}
    Visitable(size_t line_num): line_number_(line_num) {}
    Visitable(Visitable const& e): line_number_(e.line_number_) {}
    void SetLineNumber(size_t line) { line_number_ = line; }
    size_t line_number() { return line_number_; }

    virtual int accept(Visitor &v) = 0;

protected:
    size_t line_number_;
};

class InstructionBlock : public Visitable {
  public:
    InstructionBlock(): Visitable(){}
    InstructionBlock(PtrVisitable const& instr) {
        AddInstruction(instr);
    }
    InstructionBlock(InstructionBlock const& instr_block):
        Visitable(instr_block),
        instructions_(instr_block.instructions_)
    {}
    void AddInstruction(PtrVisitable instr) {
        instructions_.push_back(instr);
    }
    void operator=(InstructionBlock const& instr_block) {
        instructions_ = instr_block.instructions_;
    }
    std::vector<PtrVisitable>& instructions() { return instructions_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::vector<PtrVisitable> instructions_;
};

class Function : public Visitable {
  public:
    Function() : params_(), body_() {}
    Function(InstructionBlock const& instr_block, std::vector<std::string> const& params, size_t line_num):
        Visitable(line_num),
        params_(params),
        body_(instr_block)
    {}
    Function(Function const& f): Visitable(f), params_(f.params_), body_(f.body_) {}
    void AddParam(std::string param_name) {
        params_.push_back(param_name);
    }
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    std::vector<std::string>& params() { return params_; }
    InstructionBlock& body() { return body_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::vector<std::string> params_;
    InstructionBlock body_;
};

class ArithmExpr : public Visitable {
  public:
    ArithmExpr() {}
    ArithmExpr(ArithmExpr const& ae):
        Visitable(ae),
        operations_(ae.operations_),
        elements_(ae.elements_)
    {}
    void AddOperation(std::string operation) { operations_.push_back(operation); }
    void AddElem(PtrVisitable elem) { elements_.push_back(elem); }

    std::vector<std::string>& operations() { return operations_; }
    std::vector<PtrVisitable>& elements() { return elements_; }

    int accept(Visitor &v) = 0;

  protected:
    std::vector<std::string> operations_;
    std::vector<PtrVisitable> elements_;
};

class Term : public ArithmExpr {
public:
    Term() {}
    Term(Term const& t): ArithmExpr(t) {}
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

class Expr : public ArithmExpr {
public:
    Expr() {}
    Expr(Expr const& e): ArithmExpr(e) {}
    void AddTerm(Term const& t) {
        elements_.push_back(PtrVisitable(new Term(t)));
    }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

class Number : public Visitable {
public:
    Number(int val): value_(val) {}
    Number(std::string const& num) { value_ = atoi(num.c_str()); }
    int value() { return value_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    int value_;
};

class Assignment : public Visitable {
  public:
    Assignment(std::string id, PtrVisitable expr, size_t line_num):
        Visitable(line_num),
        id_(id),
        expr_(expr)
    {}
    Assignment(Assignment const& assign):
        Visitable(assign),
        id_(assign.id_),
        expr_(assign.expr_)
    {}
    std::string& id() { return id_; }
    PtrVisitable& expr() { return expr_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
    PtrVisitable expr_;
};

class Factor : public Visitable {
public:
    Factor() {}
    Factor(Factor const& f):
        Visitable(f),
        unary_operator_(f.unary_operator_),
        fact_expr_(f.fact_expr_)
    {}
    void SetFactExpr(PtrVisitable const& fact_expr) {
        fact_expr_ = fact_expr;
    }
    void SetUnaryOperator(std::string const& uo) { unary_operator_ = uo; }
    std::string const& unary_operator() { return unary_operator_; }
    PtrVisitable const& fact_expr() { return fact_expr_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    std::string unary_operator_;
    PtrVisitable fact_expr_;
};

class FuncCall : public Visitable {
  public:
    FuncCall(std::string& id, std::vector<Expr>& params, size_t line_num):
        Visitable(line_num),
        id_(id),
        params_(params)
    {}
    FuncCall(FuncCall const& fc):
        Visitable(fc),
        id_(fc.id_),
        params_(fc.params_)
    {}
    std::string& id() { return id_; }
    std::vector<Expr>& params() { return params_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
    std::vector<Expr> params_;
};

class PrintInstr : public Visitable {
  public:
    PrintInstr(): expr_() {}
    PrintInstr(PtrVisitable expr):
        expr_(expr)
    {}
    PrintInstr(Expr const& expr, size_t line_num):
        Visitable(line_num),
        expr_(PtrVisitable(new Expr(expr)))
    {}
    void SetExpr(Expr const& expr) {
        expr_ = PtrVisitable(new Expr(expr));
    }
    PtrVisitable& expr() { return expr_; }
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    PtrVisitable expr_;
};

class ReadInstr : public Visitable {
public:
    ReadInstr(std::string id, size_t line_num):
        Visitable(line_num),
        id_(id)
    {}
    ReadInstr(ReadInstr const& ri):
        Visitable(ri),
        id_(ri.id_) {}
    std::string& id() { return id_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    std::string id_;
};

class ReturnInstr : public Visitable {
  public:
    ReturnInstr(PtrVisitable expr) : expr_(expr) {}
    ReturnInstr(ReturnInstr const& ri):
        Visitable(ri),
        expr_(ri.expr_)
    {}
    PtrVisitable& expr() { return expr_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    PtrVisitable expr_;
};

class Variable : public Visitable {
  public:
    Variable(std::string id, size_t line_num):
        Visitable(line_num),
        id_(id)
    {}
    std::string& id() { return id_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    std::string id_;
};

class Condition : public Visitable {
  public:
    Condition() {}
    Condition(Expr e1, Expr e2, std::string comp_char):
        Visitable(),
        e1_(e1),
        e2_(e2),
        comp_char_(comp_char)
    {}
    Condition(Condition const& c):
        Visitable(c),
        e1_(c.e1_),
        e2_(c.e2_),
        comp_char_(c.comp_char_)
    {}

    Expr& e1() { return e1_; }
    Expr& e2() { return e2_; }
    std::string& comp_char() { return comp_char_; }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

  private:
    Expr e1_;
    Expr e2_;
    std::string comp_char_;
};

class ControlFlowInstr: public Visitable {
public:
  ControlFlowInstr() {}
  ControlFlowInstr(Condition const& c, InstructionBlock const& body):
      condition_(c),
      body_(body)
  {}
  ControlFlowInstr(ControlFlowInstr const& cfi):
      Visitable(cfi),
      condition_(cfi.condition_),
      body_(cfi.body_)
  {}

  Condition& condition() { return condition_; }
  InstructionBlock& body() { return body_; }

  int accept(Visitor &v) = 0;

protected:
  Condition condition_;
  InstructionBlock body_;
};

class IfInstr : public ControlFlowInstr {
  public:
    IfInstr() {}
    IfInstr(Condition const& c, InstructionBlock const& body):
        ControlFlowInstr(c, body)
    {}
    IfInstr(IfInstr const& ii):
        ControlFlowInstr(ii)
    {}

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

class WhileInstr: public ControlFlowInstr {
  public:
    WhileInstr(Condition const& c, InstructionBlock const& body):
        ControlFlowInstr(c, body)
    {}
    WhileInstr(WhileInstr const& wi): ControlFlowInstr(wi) {}
    /*virtual*/int accept(Visitor &v) { return v.visit(this); }
};

class Program: public Visitable {
  public:
    Program() {}
    Program(InstructionBlock const& ib): body_(ib), error_() {}
    Program(Program const& pr):
        Visitable(pr),
        body_(pr.body_),
        error_()
    {}
    void SetBody(InstructionBlock const& instr_block) {
        body_ = instr_block;
    }
    InstructionBlock& body() { return body_; }
    void SetError(Error e) {
        error_.Set(e.last_error_type(), e.last_error_line(), e.additional_info());
    }
    bool RuntimeErrorIsOccured() { return error_.IsOccured(); }
    std::string GetErrorMessage() { return error_.GetErrorMessage(); }

    /*virtual*/int accept(Visitor &v) { return v.visit(this); }

private:
    InstructionBlock body_;
    Error error_;
};

#endif // AST_H
