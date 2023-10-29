#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPositiveInt(char * str) {
  char * endptr;
  long value = strtol(str, &endptr, 10);
  //Check for conversion errors
  //if (value <= 0) {
  if (*endptr != '\0' || endptr == str || value <= 0) {
    return 0;  // Not a valid integer
  }
  return 1;
}

// This function to extract category within 2 "_" characters
char * category(FILE * f) {
  char * category_str = (char *)malloc(sizeof(*category_str));
  category_str[0] = '\0';
  int x;
  size_t i = 0;
  // While function, it breaks when it reaches '_'
  while ((x = fgetc(f)) != '_') {
    if (x == EOF) {
      fprintf(stderr, "Error with the category blank");
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
  return category_str;
}
void freeCategory(category_t * category) {
  for (size_t i = 0; i < category->n_words; i++) {
    free(category->words[i]);
  }
  free(category->name);
  free(category->words);
  free(category);
}
// To eliminate an element in a dynamically allocated array
category_t * eliminate_category(category_t * array, size_t size, size_t index) {
  // Allocate a copy array with size of size - 1
  category_t * temp = malloc((size - 1) * sizeof(*temp));
  // Copy memory for temp at each corner
  if (index != 0) {
    memcpy(temp, array, index * sizeof(*temp));
  }
  if (index != (size - 1)) {
    memcpy(temp + index, array + index + 1, (size - index - 1) * sizeof(*temp));
  }
  // Free the older array and return a new one
  //free(array[index].name);
  //free(array[index].words);
  free(array);
  return temp;
}
char ** eliminate_word(char ** array, size_t size, size_t index) {
  // Allocate a copy of an array of string with size -1
  char ** temp = malloc((size - 1) * sizeof(*temp));
  if (index != 0) {
    memcpy(temp, array, index * sizeof(*temp));
  }
  if (index != (size - 1)) {
    memcpy(temp + index, array + index + 1, (size - index - 1) * sizeof(*temp));
  }
  // Free old array and return a new one
  //free(array[index]);
  free(array);
  return temp;
}

// To eliminate a word in a category
void delete (catarray_t * array,
             char * category_str,
             const char * word,
             category_t * words_to_free) {
  int found = 0;
  size_t n_category = array->n;
  for (size_t i = 0; i < n_category; i++) {
    if (found == 1) {
      break;
    }
    size_t n_words = array->arr[i].n_words;
    // If the catefory exist in the array of catarray
    if (strcmp(category_str, array->arr[i].name) == 0) {
      // check if the word exists in the list of words of th category
      for (size_t j = 0; j < n_words; j++) {
        if (strcmp(word, array->arr[i].words[j]) == 0) {
          found = 1;
          //Cannot free the word here, but have to free later so save the address into an array words_to_free
          size_t n = words_to_free->n_words;
          words_to_free->words =
              realloc(words_to_free->words, (n + 1) * sizeof(words_to_free));
          words_to_free->words[n] = array->arr[i].words[j];
          //array->arr[i].words = NULL;
          words_to_free->n_words++;
          // Update the words array with a new one removing the word used
          array->arr[i].words = eliminate_word(array->arr[i].words, n_words, j);
          array->arr[i].n_words -= 1;

          // When there is no word left in the category, eliminate and free it
          if (array->arr[i].n_words == 0) {
            free(array->arr[i].name);
            free(array->arr[i].words);
            // Update the category array with a new one that removed eliminated category
            array->arr = eliminate_category(array->arr, n_category, i);
            array->n -= 1;
          }
          break;
        }
      }
    }
  }
}
// To parse the story template and replace the blank with the words
char * parsing(FILE * f, catarray_t * array, int no_reuse) {
  char * story = malloc(sizeof(*story));
  char ** strArray = NULL;
  size_t n_array = 0;
  story[0] = '\0';
  int c;
  category_t * words_to_free = malloc(sizeof(*words_to_free));
  words_to_free->name = NULL;
  words_to_free->n_words = 0;
  words_to_free->words = NULL;
  while ((c = fgetc(f)) != EOF) {
    // At the start of the blank (extracting the category)
    //int delete_word = 0;
    if (c == '_') {
      char * category_str = category(f);
      // Find the word to fill
      // Check if the word is a valid integer for reference
      if (isPositiveInt(category_str) > 0 && array != NULL) {
        size_t index = atoi(category_str);
        if (index <= 0 || index > n_array) {
          fprintf(stderr, "Invalid integer\n");
          exit(EXIT_FAILURE);
        }
        strArray = (char **)realloc(strArray, (n_array + 1) * sizeof(*strArray));
        strArray[n_array] = strArray[n_array - index];
        n_array++;
      }
      // When it is not an integer, pass it to the chooseWord function, if cannot it, chooseWord will return error
      else {
        strArray = (char **)realloc(strArray, (n_array + 1) * sizeof(*strArray));
        strArray[n_array] = (char *)chooseWord(category_str, array);
        //const char * word = chooseWord(category_str, array);
        n_array++;
        // printf("%s\n", strArray[n_array - 1]);
        // Exclude the word from the array
        if (no_reuse == 1) {
          // Check that the word must be delete from the array later
          delete (array, category_str, strArray[n_array - 1], words_to_free);
          //delete_word = 1;
        }
      }
      // Pass the right _
      c = fgetc(f);

      size_t len2 = strlen(story);
      size_t len1 = strlen(strArray[n_array - 1]);
      // Reallocate memory for story then concatenate fill to story
      story = (char *)realloc(story, (len2 + len1 + 1) * sizeof(*story));
      strcat(story, strArray[n_array - 1]);

      // Free memory of the category
      free(category_str);
    }

    // Reallocate memory for the story string
    size_t len = strlen(story);
    // Concatenate new char to the story string
    story = (char *)realloc(story, (len + 2) * sizeof(*story));
    story[len] = c;
    story[len + 1] = '\0';
  }
  // Free the array to store the filled words
  freeCategory(words_to_free);
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
  while (line[sz] != ':' && sz < len) {
    category_str = (char *)realloc(category_str, (sz + 2) * sizeof(*category_str));
    category_str[sz] = line[sz];
    category_str[sz + 1] = '\0';
    sz++;
  }
  if (sz == len) {
    fprintf(stderr, "No : found\n");
    exit(EXIT_FAILURE);
  }
  sz++;
  // Prase the word on the right of the :
  // While until it reaches \n or end of the line
  while (sz < len && line[sz] != '\n') {
    word = (char *)realloc(word, (sz_word + 2) * sizeof(*word));
    word[sz_word] = line[sz];
    word[sz_word + 1] = '\0';
    sz++;
    sz_word++;
  }

  // Error case when no word or category is found
  if (word == NULL) {
    fprintf(stderr, "No name found\n");
    exit(EXIT_FAILURE);
  }
  if (category_str == NULL && strcmp(category_str, "") == 0) {
    //if (category_str == NULL) {
    fprintf(stderr, "Read category failure, catefory NULL\n");
    exit(EXIT_FAILURE);
  }

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

        // Free the category_str, already updated a new word
        updated = 1;
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
    // Already updated a new category with new word;
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
    if (line != NULL) {
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
