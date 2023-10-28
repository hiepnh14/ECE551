#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage ./program file file\n");
    return EXIT_FAILURE;
  }
  // Initialize the array
  catarray_t * array = init_catarray();
  // Read the wordFile to the array
  readFile(array, argv[1]);

  // Open story template file
  FILE * file = fopen(argv[2], "r");
  if (file == NULL) {
    fprintf(stderr, "Fail to open the input file\n");
    return EXIT_FAILURE;
  }
  // Parse the story template and fill in the blank with words from the array
  char * story = parsing(file, array, 0);
  fprintf(stdout, "%s", story);

  // Free memory for story
  free(story);
  freeCat(array);
  // Close the file
  if (fclose(file) != 0) {
    fprintf(stderr, "Fail to close the input file2\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
