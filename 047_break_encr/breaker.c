#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void frequency_count(FILE * f, int * frequency) {
  int c;
  int check_point = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      //printf("%c", c);
      c -= 'a';
      frequency[c] += 1;
      check_point = 1;
    }
  }
  if (check_point == 0) {
    fprintf(stderr, "No text detected!\n");
    exit(EXIT_FAILURE);
  }
}

int most_frequent(int * frequency) {
  int index = 0;
  int temp = frequency[0];
  for (int i = 1; i < 26; i++) {
    // printf("In the loop\n");
    if (frequency[i] > temp) {
      temp = frequency[i];
      index = i;
      // printf("Update index to %d", i);
    }
  }
  index -= 4;  // 'e' is the most frequent character
  if (index < 0) {
    index += 26;
  }
  return index;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int frequency[26] = {0};
  frequency_count(f, frequency);
  //  for (int i = 0; i < 26; i++) {
  //printf("%d\n", frequency[i]);
  // }
  printf("%d\n", most_frequent(frequency));
  if (fclose(f) != 0) {
    perror("Fail to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
