
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
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
  virtual ~PlusExpression() {
    delete exp1;
    delete exp2;
  }
};
