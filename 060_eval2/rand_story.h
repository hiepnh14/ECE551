#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

char * category(FILE * f);
char * parsing(FILE * f, catarray_t * array, int no_reuse);
catarray_t * init_catarray(void);
void readFile(catarray_t * catarray, char * filename);
void freeCat(catarray_t * catarray);
//any functions you want your main to use

#endif
