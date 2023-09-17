#include <stdio.h>

unsigned power(unsigned int x, unsigned y) {
  // Bases base: If y is 0, x^0 is 1.
  if (y == 0) {
    return 1;
  }
  // Recursive case: x^y = x * (x^(y-1))
  return x * power(x, y - 1);
}
