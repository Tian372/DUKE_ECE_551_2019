#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned ea) {
  if (power(x, y) != ea) {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  for (unsigned i = 0; i <= 8000; i++) {
    run_check(i, 0, 1);
    run_check(i, 1, i);
    run_check(1, i, 1);
  }
  run_check(10, 2, 100);
  run_check(2, 2, 4);
  run_check(4294967295, 1, 4294967295);

  exit(EXIT_SUCCESS);
}
