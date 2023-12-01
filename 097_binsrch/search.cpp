#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high < low)
    exit(EXIT_FAILURE);
  if (low == high || low == high - 1)
    return low;
  int x = (high + low) / 2;
  int y = f->invoke(x);
  if (y == 0) {
    return x;
  }
  if (y > 0)
    return binarySearchForZero(f, low, x);
  if (y < 0)
    return binarySearchForZero(f, x, high);
  return low;
  //if (f->invoke(low) >= 0)
  //return low;
  //high = high - 1;
  //if (f->invoke(high) <= 0)
  //return high;
  //while (low <= high) {
  //x = (high + low) / 2;
  // y = f->invoke(x);
  //if (y == 0)
  //  return x;
  //else if (y < 0) {
  //  low = x + 1;
  //}
  //else {
  //  high = x - 1;
  //}
  //}
  //if (y > 0)
  //return low;
  //return x;
}
