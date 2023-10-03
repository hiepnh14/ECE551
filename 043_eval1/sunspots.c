#include "sunspots.h"

#include <stdlib.h>
#include <string.h>

ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  int year, month;
  float num;
  if (sscanf(line, "%d-%d,%f", &year, &month, &num) != EOF) {
    ans.year = year;
    ans.month = month;
    ans.num = num;
    return ans;
  }
  else
    exit(EXIT_FAILURE);
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  return 0;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  return 0;
}
