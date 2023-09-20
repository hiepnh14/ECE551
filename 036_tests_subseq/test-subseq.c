#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void checker(int * array, size_t n, size_t expected) {
  if (maxSeq(array, n) != expected) {
    printf("result = %ld, expected = %ld\n", maxSeq(array, n), expected);
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  int test1[] = {1, 2, 2, 2, 2, 3};
  int test2[] = {3, 1, 2};
  int test3[] = {0};
  int test4[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int test5[] = {-10, -4, 2, -10};
  int test6[] = {1000000000, -100000000, 0, 1};
  int test7[] = {1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6};
  int test8[] = {1, 2, 3, 4, 3, 4, 1, 2, 0, 0};

  checker(test1, 6, 2);
  checker(NULL, 0, 0);
  checker(test2, 3, 2);
  checker(test3, 1, 1);
  checker(test4, 10, 4);
  checker(test5, 4, 3);
  checker(test6, 4, 3);
  checker(test7, 11, 7);
  checker(test8, 10, 4);

  printf("Passed all check points");
  return EXIT_SUCCESS;
}
