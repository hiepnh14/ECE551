#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void check(unsigned x, unsigned y, long expected) {
  if (power(x, y) != expected) {
    printf("Computed wrongly at %d to the power of %d\n", x, y);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  check(0, 1, 0);
  check(0, 0, 1);
  check(1, 0, 1);
  check(2, 0, 1);
  check(4, 5, 1024);
  check(0, 10, 0);
  check(9, 2, 81);
  check(1, 1, 1);
  check(1, 2, 1);
  check(1, 100, 1);
  check(2, 1, 2);
  check(2, 2, 4);
  check(0, 2, 0);
  check(10, 6, 1000000);
  check(-1, 0, 0);
  check(-1, 1, -1);
  check(2, 30, 10737411824);
  printf("Pass all cases\n");
  return EXIT_SUCCESS;
}
