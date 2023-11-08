#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
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
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
