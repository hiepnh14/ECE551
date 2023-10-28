#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPositiveInt(char * str) {
  char * endptr;
  long value = strtol(str, &endptr, 10);
  //Check for conversion errors
  if (*endptr != '\0' || endptr == str || value <= 0) {
    return 0;  // Not a valid integer
  }
  return 1;
}

// This function to extract category within 2 "_" characters
char * category(FILE * f) {
  char * category_str = NULL;
  int x;
  size_t i = 0;
  // While function, it breaks when it reaches '_'
  while ((x = fgetc(f)) != '_') {
    // int length = strlen(category_str);
    if (x == ' ' || x == EOF) {
      fprintf(stderr, "Error with the black\n");
      exit(EXIT_FAILURE);
    }

    category_str = (char *)realloc(category_str, (i + 2) * sizeof(*category_str));
    // Add the character to the category
    if (category_str == NULL) {
      fprintf(stderr, "Cannot reallocate memory for category_str");
    }
    category_str[i] = x;
    // Mark the end of the string
    category_str[i + 1] = '\0';
    i++;
  }
  // printf("%s\n", category_str);
  return category_str;
}

// To parse the story template and replace the blank with the words
char * parsing(FILE * f, catarray_t * array) {
  char * story = malloc(sizeof(*story));
  char ** strArray = NULL;
  size_t n_array = 0;
  story[0] = '\0';
  int c;
  while ((c = fgetc(f)) != EOF) {
    // At the start of the blank (extracting the category)
    if (c == '_') {
      char * category_str = category(f);
      // Find the word to fill
      // printf("%s\n", category_str);
      if (isPositiveInt(category_str) > 0) {
        size_t index = atoi(category_str);
        if (index <= 0 || index > n_array) {
          fprintf(stderr, "Invalid integer\n");
          exit(EXIT_FAILURE);
        }
        strArray = (char **)realloc(strArray, (n_array + 1) * sizeof(*strArray));
        strArray[n_array] = strArray[n_array - index];
        n_array++;
      }
      else {
        strArray = (char **)realloc(strArray, (n_array + 1) * sizeof(*strArray));
        strArray[n_array] = (char *)chooseWord(category_str, array);
        n_array++;
      }
      // Free the memory allocate for category
      free(category_str);
      // Pass the right _
      c = fgetc(f);
      size_t len2 = strlen(story);
      size_t len1 = strlen(strArray[n_array - 1]);
      // Reallocate memory for story then concatenate fill to story
      story = (char *)realloc(story, (len2 + len1 + 1) * sizeof(*story));
      strcat(story, strArray[n_array - 1]);
    }

    // Reallocate memory for the story string
    size_t len = strlen(story);
    story = (char *)realloc(story, (len + 2) * sizeof(*story));
    story[len] = c;
    story[len + 1] = '\0';
  }
  free(strArray);
  return story;
}

// To initialize catarray pointer
catarray_t * init_catarray(void) {
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  return catarray;
}

// To read one line of Category:word
void readWords(catarray_t * catarray, char * line) {
  char * word = (char *)malloc(sizeof(*word));
  word[0] = '\0';
  char * category_str = (char *)malloc(sizeof(*category_str));
  category_str[0] = '\0';
  size_t len = strlen(line);
  size_t sz = 0;
  size_t sz_word = 0;
  // Parse the category on the left of the :
  while (line[sz] != ':') {
    category_str = (char *)realloc(category_str, (sz + 2) * sizeof(*category_str));
    category_str[sz] = line[sz];
    category_str[sz + 1] = '\0';
    sz++;
  }

  sz++;
  // Prase the word on the right of the :
  //while ((isalpha(line[sz]) != 0 || line[sz] == ' ') && sz < len) {
  while (sz < len && line[sz] != '\n') {
    word = (char *)realloc(word, (sz_word + 2) * sizeof(*word));
    word[sz_word] = line[sz];
    word[sz_word + 1] = '\0';
    sz++;
    sz_word++;
  }

  //char * p = strchr(line, ':');
  //char * category_str = strsep(&line, ":");
  //if (category_str == NULL) {
  //fprintf(stderr, "No Category found\n");
  //exit(EXIT_FAILURE);
  //}
  //char * word = p;
  //strtok(word, "\n");
  if (word == NULL) {
    fprintf(stderr, "No name found\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(category_str, "") == 0) {
    fprintf(stderr, "Read category failure, catefory NULL\n");
    exit(EXIT_FAILURE);
  }
  //printf("%s:%s\n", category_str, word);
  int updated = 0;  // Set a flag to update the word to the category
  for (size_t i = 0; i < catarray->n; i++) {
    // If the catefory exist in the array of catarray
    if (strcmp(category_str, catarray->arr[i].name) == 0) {
      // check if the word exists in the list of words of th category
      for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
        if (strcmp(word, catarray->arr[i].words[j]) == 0) {
          updated = 1;
          break;
        }
      }
      // Word does not exist in the category, category exists
      if (updated == 0) {
        size_t n = catarray->arr[i].n_words;
        catarray->arr[i].words =
            realloc(catarray->arr[i].words, (n + 1) * sizeof(*catarray->arr[i].words));
        catarray->arr[i].words[n] = word;
        catarray->arr[i].n_words++;

        // Free the category_str
        updated = 1;
        //printf("Adding %s to %s\n", catarray->arr[i].words[n], catarray->arr[i].name);
        free(category_str);
        break;
      }
    }
  }
  // When the category does not exist in the current array
  if (updated == 0) {
    size_t n = catarray->n;
    catarray->arr = realloc(catarray->arr, (n + 1) * sizeof(*catarray->arr));
    catarray->arr[n].name = category_str;
    catarray->arr[n].words = malloc(sizeof(*catarray->arr[n].words));
    catarray->arr[n].words[0] = word;
    catarray->arr[n].n_words = 1;
    catarray->n++;
    // printf("Adding %s\n", category_str);
    updated = 1;
  }
  // Handle duplicate name, word, category
  // Update the array
  // Free memory if there is any extra that is not stored in the array
}
// Read the words file
void readFile(catarray_t * catarray, char * filename) {
  size_t sz = 0;
  char * line = NULL;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the word file");
    exit(EXIT_FAILURE);
  }
  // Read line by line and update to the catarray;
  while ((getline(&line, &sz, f)) >= 0) {
    if (line != NULL && strlen(line) > 2) {
      readWords(catarray, line);
    }
    else {
      fprintf(stderr, "Line sintax in word file is not correct\n");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file\n");
    exit(EXIT_FAILURE);
  }
}

// To free all the memory of catarray
void freeCat(catarray_t * catarray) {
  size_t n = catarray->n;
  for (size_t i = 0; i < n; i++) {
    size_t m = catarray->arr[i].n_words;
    for (size_t j = 0; j < m; j++) {
      // Free the string of words
      free(catarray->arr[i].words[j]);
    }
    // Free the name of category
    free(catarray->arr[i].name);
    // Free the array of words
    free(catarray->arr[i].words);
  }
  // Free array
  free(catarray->arr);
  // Free pointer
  free(catarray);
}
