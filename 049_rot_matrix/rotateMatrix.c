#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readMatrix(FILE * f, char (*matrix)[10]) {
  char c;
  int row = 0;
  int column = 0;
  int check_point = 0;
  while (((c = fgetc(f)) != EOF)) {
    if (row > 9) {
      fprintf(stderr, "Usage: matrix has more than 10 rows");
      exit(EXIT_FAILURE);
    }
    if (c != '\n') {
      check_point = 1;
      matrix[row][column] = c;
      column++;
    }
    else if ((c == '\n') && (column == 10)) {
      column = 0;
      row++;
    }
    else if ((c == '\n') && (column == 0)) {
      row -= 1;
    }
    else if ((c == '\n') && (column != 10)) {
      fprintf(stderr, "Usage: matrix has %d columns in row: %d", column, row);
      exit(EXIT_FAILURE);
    }
  }
  if (check_point == 0) {
    fprintf(stderr, "No data input to matrix\n");
    exit(EXIT_FAILURE);
  }
}

void rotateMatrix(char (*a)[10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = i; j < 10; j++) {
      char temp = a[i][j];
      a[i][j] = a[j][i];
      a[j][i] = temp;
    }
  }
  for (int j = 0; j < 10 / 2; j++) {
    for (int i = 0; i < 10; i++) {
      char temp = a[i][j];
      a[i][j] = a[i][9 - j];
      a[i][9 - j] = temp;
    }
  }
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix fileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  readMatrix(f, matrix);
  rotateMatrix(matrix);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    perror("Fail to close the input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
