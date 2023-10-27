#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage ./rand_story inputFile");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open inputfile");
    return EXIT_FAILURE;
  }
  // Initialize the array
  catarray_t * array = init_catarray();

  readFile(array, f);
  printWords(array);

  // Free memory for the array
  freeCat(array);
  // Closing the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the input file");
    return EXIT_FAILURE;
  }
}
