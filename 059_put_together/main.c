#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * counts = createCounts();
  //size_t numArray = kvPairs->length;
  FILE * read = fopen(filename, "r");
  if (read == NULL) {
    fprintf(stderr, "The reading file is NULL");
    return (NULL);
  }
  char * line = NULL;
  size_t sz = 0;
  // Read the filename for key, then lookup for value in kvPairs then add it to the counts
  while (getline(&line, &sz, read) >= 0) {
    //if (line == NULL) {
    //continue;
    //}
    //stripNewline(line);
    //char * value = lookupValue(kvPairs, line);
    //printf("%s\n", lookupValue(kvPairs, line));
    //char * p = strchr(line, '\n');
    //size_t len = p - line;
    //char * newline = malloc((len + 1) * sizeof(*newline));
    //strncpy(newline, line, p - line);
    //newline[len] = '\0';
    char * newline = malloc(strlen(line) * sizeof(*newline));
    strcpy(newline, line);
    stripNewline(newline);
    printf("%s\n", newline);
    addCount(counts, lookupValue(kvPairs, newline));
    free(newline);
    //free(line);
  }
  //char * outFile = computeOutputFileName(filename);
  free(line);
  if (fclose(read) != 0) {
    fprintf(stderr, "Cannot close the file");
    exit(EXIT_FAILURE);
  }

  //printCounts(counts, outFile);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Usage: ./main key/valueFile countFiles");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    FILE * f = fopen(outName, "w");
    //open the file named by outName (call that f)
    printCounts(c, f);
    if (fclose(f) != 0) {
      fprintf(stderr, "CAnnot close output File");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f

    //close f
    free(outName);
    freeCounts(c);
    //free the memory for outName and c
  }
  freeKVs(kv);
  //free the memory for kv

  return EXIT_SUCCESS;
}
