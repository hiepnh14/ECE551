#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage ./rand_story inputFile");
    return EXIT_FAILURE;
  }
  // Initialize the array
  catarray_t * array = init_catarray();

  readFile(array, argv[1]);
  printWords(array);

  // Free memory for the array
  freeCat(array);
  // Closing the file
}
