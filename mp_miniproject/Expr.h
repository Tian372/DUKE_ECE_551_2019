#ifndef __Expr__
#define __Expr__
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

// quote from 085 expr_eval3

class Expression {
 public:
  virtual double evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  double number;

 public:
  NumExpression(double input) : number(input) {}
  virtual double evaluate() const { return number; }

  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  PlusExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};

  virtual double evaluate() const {
    return exp1->evaluate() + exp2->evaluate();
  };
  virtual ~PlusExpression() {
    delete exp1;
    delete exp2;
  }
};

class MinusExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  MinusExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return exp1->evaluate() - exp2->evaluate();
  };
  virtual ~MinusExpression() {
    delete exp1;
    delete exp2;
  }
};

class TimesExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  TimesExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return exp1->evaluate() * exp2->evaluate();
  };
  virtual ~TimesExpression() {
    delete exp1;
    delete exp2;
  }
};

class DivExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  DivExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return exp1->evaluate() / exp2->evaluate();
  }
  virtual ~DivExpression() {
    delete exp1;
    delete exp2;
  }
};
class ModExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  ModExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return fmod(exp1->evaluate(), exp2->evaluate());
  }
  virtual ~ModExpression() {
    delete exp1;
    delete exp2;
  }
};

class PowExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  PowExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return pow(exp1->evaluate(), exp2->evaluate());
  }
  virtual ~PowExpression() {
    delete exp1;
    delete exp2;
  }
};

class SqrtExpression : public Expression {
 private:
  Expression* exp1;

 public:
  SqrtExpression(Expression* lhs) : exp1(lhs) {}
  virtual double evaluate() const { return sqrt(exp1->evaluate()); }
  virtual ~SqrtExpression() { delete exp1; }
};

class floorExpression : public Expression {
 private:
  Expression* exp1;

 public:
  floorExpression(Expression* lhs) : exp1(lhs) {}
  virtual double evaluate() const { return floor(exp1->evaluate()); }
  virtual ~floorExpression() { delete exp1; }
};

class ceilExpression : public Expression {
 private:
  Expression* exp1;

 public:
  ceilExpression(Expression* lhs) : exp1(lhs) {}
  virtual double evaluate() const { return ceil(exp1->evaluate()); }
  virtual ~ceilExpression() { delete exp1; }
};

class roundExpression : public Expression {
 private:
  Expression* exp1;

 public:
  roundExpression(Expression* lhs) : exp1(lhs) {}
  virtual double evaluate() const { return round(exp1->evaluate()); }
  virtual ~roundExpression() { delete exp1; }
};

class LogbExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;

 public:
  LogbExpression(Expression* lhs, Expression* rhs) : exp1(lhs), exp2(rhs){};
  virtual double evaluate() const {
    return log10(exp1->evaluate()) / log10(exp2->evaluate());
  }
  virtual ~LogbExpression() {
    delete exp1;
    delete exp2;
  }
};

class selectExpression : public Expression {
 private:
  Expression* exp1;
  Expression* exp2;
  Expression* exp3;

 public:
  selectExpression(Expression* lhs, Expression* rhs, Expression* e3)
      : exp1(lhs), exp2(rhs), exp3(e3){};
  virtual double evaluate() const {
    if (exp1->evaluate() >= 0) {
      return exp2->evaluate();
    } else {
      return exp3->evaluate();
    }
  }
  virtual ~selectExpression() {
    delete exp1;
    delete exp2;
    delete exp3;
  }
};

#endif
