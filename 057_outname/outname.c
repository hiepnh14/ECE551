#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * suffix = ".counts";
  size_t len = strlen(inputName) + strlen(suffix) + 1;
  char * output = malloc(len * sizeof(output));
  strcpy(output, inputName);
  strcat(output, suffix);
  return output;
}
