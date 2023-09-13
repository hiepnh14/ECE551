#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int months = startAge;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", (months / 12), months % 12, balance);
    balance += working.contribution + balance * working.rate_of_return;
    months += 1;
  }

  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2f\n", (months / 12), months % 12, balance);
    balance += balance * retired.rate_of_return + retired.contribution;
    months += 1;
  }
}
int main(void) {
  retire_info working, retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
