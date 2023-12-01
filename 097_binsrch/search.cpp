#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high)
    return low;

  if (f->invoke(low) >= 0)
    return low;
  high = high - 1;
  if (f->invoke(high) < 0)
    return high;
  int x = (high + low) / 2;
  int y;
  while (low <= high) {
    y = f->invoke(x);
    if (y == 0)
      return x;
    else if (y < 0) {
      low = x + 1;
      x = (high + low) / 2;
    }
    else {
      high = x - 1;
      x = (high + low) / 2;
    }
  }
  if (y > 0)
    return x - 1;
  return x;
}
