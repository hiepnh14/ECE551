#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * readPair(char * line) {
  //pair->key = strtok(line, "=");
  kvpair_t * pair = malloc(sizeof(*pair));
  char * p = strchr(line, '=');
  pair->key = strsep(&line, "=");
  if (pair->key == NULL) {
    fprintf(stderr, "No key found\n");
    exit(EXIT_FAILURE);
  }

  pair->value = p + 1;
  strtok(pair->value, "\n");

  if (pair->value == NULL) {
    fprintf(stderr, "No value found\n");
    exit(EXIT_FAILURE);
  }
  return pair;
  //printf("%s, %s\n", pair->key, pair->value);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  char * line = NULL;
  size_t sz = 0;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "The file is NULL");
    return (NULL);
  }
  kvpair_t ** array = NULL;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    array = realloc(array, (i + 1) * sizeof(*array));
    array[i] = readPair(line);
    line = NULL;
    i++;
  }
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->pairs = array;
  ans->length = i;
  //free(array);
  //fclose(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close the file");
    exit(EXIT_FAILURE);
  }
  free(line);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  size_t length = pairs->length;
  for (size_t i = 0; i < length; i++) {
    free(pairs->pairs[i]->key);
    //free(pairs->pairs[i]->value);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}
//WRITE ME

void printKVs(kvarray_t * pairs) {
  size_t length = pairs->length;
  for (size_t i = 0; i < length; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->pairs[i])->key, (pairs->pairs[i])->value);
  }
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t length = pairs->length;
  for (size_t i = 0; i < length; i++) {
    if (strcmp((pairs->pairs[i])->key, key) == 0) {
      return (pairs->pairs[i])->value;
    }
  }
  return NULL;
}
