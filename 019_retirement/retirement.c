#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double new_b(double balance, retire_info A) {
  return balance + balance * A.rate_of_return + A.contribution;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int age = startAge / 12;
  int mon = startAge % 12;

  for (int i = 0; i < (working.months + retired.months); i++) {
    mon = (i + startAge % 12) % 12;

    if ((i + startAge % 12) % 12 == 0) {
      age++;
    }

    if (i < working.months) {
      printf("Age %3d month %2d you have $%.2lf\n", age, mon, balance);
      balance = new_b(balance, working);
    }
    else {
      printf("Age %3d month %2d you have $%.2lf\n", age, mon, balance);
      balance = new_b(balance, retired);
    }
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double saving = 21345;

  retirement(startAge, saving, working, retired);
  return EXIT_SUCCESS;
}
