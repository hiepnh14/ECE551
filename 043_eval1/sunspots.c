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
  double sum = 0;
  unsigned long count = 0;
  unsigned long radius = (w - 1) / 2;
  for (size_t i = 0; i < n; i++) {
    sum = 0;
    count = 0;
    // Left bound
    if (i < radius) {
      for (size_t j = 0; j <= (i + radius); j++) {
        sum += data[j].num;
        count++;
      }
    }
    else if ((i + radius) > (n - 1)) {
      for (size_t j = i - radius; j < n; j++) {
        sum += data[j].num;
        count++;
      }
    }
    else {
      for (size_t j = (i - radius); j <= (i + radius); j++) {
        sum += data[j].num;
        count++;
      }
    }
    mean[i].month = data[i].month;
    mean[i].year = data[i].year;
    mean[i].num = sum / count;
    //printf("%lf, %ld\n", mean[i].num, count);
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  return 0;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  return 0;
}
