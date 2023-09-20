#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t temp = 1;
  size_t max = 1;
  if (n == 0)
    return 0;
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      temp++;
      if (temp > max)
        max = temp;
    }
    else {
      if (temp > max) {
        max = temp;
      }
      temp = 1;
    }
  }
  return max;
}
