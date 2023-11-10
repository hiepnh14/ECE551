#include <cstdio>
#include <cstdlib>
#include <ostream>
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
class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs_in, Expression * rhs_in) : lhs(lhs_in), rhs(rhs_in) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs_in, Expression * rhs_in) : lhs(lhs_in), rhs(rhs_in) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs_in, Expression * rhs_in) : lhs(lhs_in), rhs(rhs_in) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs_in, Expression * rhs_in) : lhs(lhs_in), rhs(rhs_in) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    std::string result = stream.str();
    return result;
  }
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
