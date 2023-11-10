#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    //to print out
    std::stringstream stream;
    stream << number;
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const { return number; }
  virtual ~NumExpression(){};
};

class Operation : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;
  const char * operate;

 public:
  Operation(Expression * lhs_in, Expression * rhs_in, const char * operate) :
      lhs(lhs_in), rhs(rhs_in), operate(operate) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << " " << *operate << " " << rhs->toString() << ")";
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const {
    switch (*operate) {
      case '+':
        return lhs->evaluate() + rhs->evaluate();
      case '-':
        return lhs->evaluate() - rhs->evaluate();
      case '*':
        return lhs->evaluate() * rhs->evaluate();
      case '/':
        return lhs->evaluate() / rhs->evaluate();
      default:
        std::cerr << "Cannot operate " << *operate << std::endl;
        abort();
    }
  }
  virtual ~Operation() {
    delete lhs;
    delete rhs;
  }
};
class PlusExpression : public Operation {
 public:
  PlusExpression(Expression * lhs_in, Expression * rhs_in) :
      Operation(lhs_in, rhs_in, "+") {}
};

class MinusExpression : public Operation {
 public:
  MinusExpression(Expression * lhs_in, Expression * rhs_in) :
      Operation(lhs_in, rhs_in, "-") {}
};

class TimesExpression : public Operation {
 public:
  TimesExpression(Expression * lhs_in, Expression * rhs_in) :
      Operation(lhs_in, rhs_in, "*") {}
};

class DivExpression : public Operation {
 public:
  DivExpression(Expression * lhs_in, Expression * rhs_in) :
      Operation(lhs_in, rhs_in, "/") {}
};
