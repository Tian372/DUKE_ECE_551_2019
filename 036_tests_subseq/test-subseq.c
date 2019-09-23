#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

void check_it(int * array, size_t n, size_t b) {
  size_t a = maxSeq(array, n);

  if (a != b) {
    printf("Failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array2[7] = {-1, 0, 1, 2, 4, 3, 5};
  int array3[7] = {1, 1, 1, 3, 5, 8, 1};
  int array4[7] = {-4, -3, -2, -1, 0, -5, -6};
  int array5[5] = {1, 1, 1, 1, 1};
  int array6[6] = {0};
  int array7[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int array8[3] = {3, 2, 1};
  int array9[1] = {2};
  int array10[6] = {-1, -2, -3, 0, 3, 8};
  int array11[12] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3, 4};
  int array12[0];
  check_it(array1, 10, 4);
  check_it(array2, 7, 5);
  check_it(array3, 7, 4);
  check_it(array4, 7, 5);
  check_it(array5, 5, 1);
  check_it(array6, 6, 1);
  check_it(array7, 8, 8);
  check_it(array8, 8, 1);
  check_it(array9, 1, 1);
  check_it(array10, 6, 4);
  check_it(array11, 12, 5);
  check_it(array12, 0, 0);

  printf("Passed\n");
  exit(EXIT_SUCCESS);
}