#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 1; }
};
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  if (low < high) {
    int f_low = f->invoke(low);
    int f_high = f->invoke(high - 1);
    CountedIntFn counting((log2(high - low)) + 1, f, mesg);
    int f_zero = binarySearchForZero(&counting, low, high);
    //std::cout << f_low << " " << f_zero << " " << f_high << mesg << std::endl;
    //int f_zero = binarySearchForZero(f, low, high);
    assert(expected_ans == f_zero);
    assert((f_low < 0 && f_high >= 0 && f_zero == expected_ans) ||
           (f_low < 0 && f_high < 0 && f_zero == high - 1) ||
           (f_low >= 0 && f_high > 0 && f_zero == low));
  }
  else {
    CountedIntFn counting(1, f, mesg);
    int f_zero = binarySearchForZero(&counting, low, high);
    assert(f_zero == expected_ans);
  }
}
int main(void) {
  SinFunction Sin;
  LinearFunction Linear;
  check(&Sin, 0, 150000, 52359, "Checking for SinFunction");
  check(&Sin, 52359, 150000, 52359, "Checking for SinFunction1");
  check(&Sin, 0, 50001, 50000, "Checking for another Sin");
  check(&Sin, 60000, 120000, 60000, "Checking for another Sin2");
  check(&Sin, 52358, 52362, 52359, "Checking for another Sin3");
  check(&Linear, 0, 4, 1, "Linear 1");
}
