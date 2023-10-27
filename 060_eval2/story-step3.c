#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage ./program file file\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open inputfile\n");
    return EXIT_SUCCESS;
  }
  // Initialize the array
  catarray_t * array = init_catarray();

  readFile(array, f);
  // printWords(array);
  // Closing the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the input file\n");
    return EXIT_FAILURE;
  }
  // Open story template file
  FILE * file = fopen(argv[2], "r");
  if (file == NULL) {
    fprintf(stderr, "Fail to open the input file\n");
    return EXIT_FAILURE;
  }
  char * story = parsing(file, array);
  fprintf(stdout, "%s", story);

  // Free memory for story
  free(story);
  // Close the file
  if (fclose(file) != 0) {
    fprintf(stderr, "Fail to close the input file2\n");
    return EXIT_FAILURE;
  }
  freeCat(array);
}
