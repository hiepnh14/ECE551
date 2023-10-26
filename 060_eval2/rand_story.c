#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * parsing(FILE * f) {
  char * story = NULL;
  char c;
  while ((c = fgetc(f)) != EOF) {
    // At the start of the blank (extracting the category)
    if (c == '_') {
      char category[30] = "";
      char x;
      while ((x = fgetc(f)) != '_') {
        // Check for fail case of category
        int length = strlen(category);
        if (x == ' ' || x == EOF) {
          fprintf(stderr, "Error with the blank\n");
          exit(EXIT_FAILURE);
        }
        if ((length + 1) >= 30) {
          fprintf(stderr, "Category name at the blank too long\n");
          exit(EXIT_FAILURE);
        }
        // Add the character to the category
        category[length] = x;
        // Mark the end of the string for category
        category[length + 1] = '\0';
      }
      // Find the word to fill
      const char * fill = chooseWord(category, NULL);
      // Reallocate memory for story then concatenate fill to story
      story = realloc(story, (strlen(story) + strlen(fill) + 1) * sizeof(*story));
      strcat(story, fill);
    }
    // Reallocate memory for the story string
    int len = strlen(story);
    story = realloc(story, (len + 1) * sizeof(*story) + sizeof(c));
    story[len] = c;
    story[len + 1] = '\0';
  }
  return story;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage ./ rand_story input_file");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open input file");
    return EXIT_FAILURE;
  }

  char * story;
  story = parsing(f);

  fprintf(stdout, "%s", story);
  free(story);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
