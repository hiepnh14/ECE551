#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->counts = NULL;
  c->numCount = 0;
  c->unknownCount = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknownCount++;
    return;
  }
  int len = c->numCount;
  for (int i = 0; i < len; i++) {
    if (strcmp(c->counts[i]->key, name) == 0) {
      c->counts[i]->count++;
      return;
    }
  }
  c->counts = realloc(c->counts, (len + 1) * sizeof(*c->counts));
  c->counts[len] = malloc(sizeof(*c->counts[len]));
  c->counts[len]->key = name;
  c->counts[len]->count++;
  c->numCount++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c == NULL) {
    fprintf(stderr, "No data in counts");
    exit(EXIT_FAILURE);
  }
  if (outFile == NULL) {
    fprintf(stderr, "Cannot open outFile");
    exit(EXIT_FAILURE);
  }
  int len = c->numCount;
  for (int i = 0; i < len; i++) {
    fprintf(outFile, "%s: %ld\n", c->counts[i]->key, c->counts[i]->count);
  }
  if (c->unknownCount != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknownCount);
  }
  if (fclose(outFile) != 0) {
    fprintf(stderr, "Fail to close the file");
    exit(EXIT_FAILURE);
  }
}
void freeCounts(counts_t * c) {
  //WRITE ME
  int len = c->numCount;
  for (int i = 0; i < len; i++) {
    //free(c->counts[i]->key);
    //free(c->counts[i]->count);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
