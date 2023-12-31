#include <stdio.h>

int max(int num1, int num2) {
  if (num1 > num2) {
    return num1;
  }
  else
    return num2;
}
int check(int num1, int num2, int num3) {
  if ((num1 == num2) || (num1 == num3)) {
    return 0;
  }
  else
    return 1;
}

int range(int num, int lower, int upper) {
  if ((num >= lower) && (num < upper)) {
    return 0;
  }
  else
    return 1;
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, (x_offset + size2));
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, (y_offset + size2));
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (((range(x, x_offset, x_offset + size2) == 0) &&
           (check(y, y_offset, y_offset + size2 - 1) == 0)) ||
          ((range(y, y_offset, y_offset + size2) == 0) &&
           (check(x, x_offset, x_offset + size2 - 1) == 0))) {
        printf("*");
      }
      //count from 0 to w. Call the number you count with x
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
      else if (((x < size1) && (check(y, 0, size1 - 1) == 0)) ||
               ((y < size1) && (check(x, 0, size1 - 1) == 0))) {
        printf("#");
        //if not,
        // check if EITHER
        //    x is less than size1 AND (y is either 0 or size1-1)
        // OR
        //    y is less than size1 AND (x is either 0 or size1-1)
        //if so, print a #
      }
      else
        printf(" ");
    }
    printf("\n");
  }
  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
