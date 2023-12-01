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
}
