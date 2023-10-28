#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "Usage ./program (-n) wordFile storyFile\n");
    return EXIT_FAILURE;
  }
  char * wordfile;
  char * storyfile;
  // Mark for the option of not reusing words
  int no_use = -1;
  // Initialize the array
  catarray_t * array = init_catarray();
  if (argc == 3) {
    wordfile = argv[1];
    storyfile = argv[2];
    // Allow to reuse words
    no_use = 0;
  }
  if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    wordfile = argv[2];
    storyfile = argv[3];
    // Not allow to reuse words
    no_use = 1;
  }
  readFile(array, wordfile);
  // Closing the file
  // Open story template file
  FILE * file = fopen(storyfile, "r");
  if (file == NULL) {
    fprintf(stderr, "Fail to open the input file\n");
    return EXIT_FAILURE;
  }

  // Parsing the story template
  char * story = parsing(file, array, no_use);
  fprintf(stdout, "%s", story);

  // Free memory for story and catarray_t array
  free(story);
  freeCat(array);

  // Close the story file
  if (fclose(file) != 0) {
    fprintf(stderr, "Fail to close the input file2\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
