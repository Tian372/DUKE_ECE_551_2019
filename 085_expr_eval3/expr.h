#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long x;

 public:
  NumExpression(long i) : x(i) {}

  virtual std::string toString() const {
    std::stringstream s;
    s << x;
    return s.str();
  }
  virtual long evaluate() const { return x; };
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * exp1;
  Expression * exp2;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : exp1(lhs), exp2(rhs){};

  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << exp1->toString() << " + " << exp2->toString() << ")";
    return s.str();
  }
  virtual long evaluate() const {
    long sum;
    sum = exp1->evaluate() + exp2->evaluate();
    return sum;
  };
  virtual ~PlusExpression() {
    delete exp1;
    delete exp2;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * exp1;
  Expression * exp2;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : exp1(lhs), exp2(rhs){};

  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << exp1->toString() << " - " << exp2->toString() << ")";
    return s.str();
  }
  virtual long evaluate() const {
    long sub;
    sub = exp1->evaluate() - exp2->evaluate();
    return sub;
  };
  virtual ~MinusExpression() {
    delete exp1;
    delete exp2;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * exp1;
  Expression * exp2;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : exp1(lhs), exp2(rhs){};

  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << exp1->toString() << " * " << exp2->toString() << ")";
    return s.str();
  }
  virtual long evaluate() const {
    long multi;
    multi = exp1->evaluate() * exp2->evaluate();
    return multi;
  };
  virtual ~TimesExpression() {
    delete exp1;
    delete exp2;
  }
};

class DivExpression : public Expression {
 private:
  Expression * exp1;
  Expression * exp2;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : exp1(lhs), exp2(rhs){};

  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << exp1->toString() << " / " << exp2->toString() << ")";
    return s.str();
  }
  virtual long evaluate() const {
    long div;
    div = exp1->evaluate() / exp2->evaluate();
    return div;
  };
  virtual ~DivExpression() {
    delete exp1;
    delete exp2;
  }
};
