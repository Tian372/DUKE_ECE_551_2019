// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  int y = (x + 1) * (x + 1) + x;

  if ((x - 2) % 4 == 0) {
    y = 2 * x;
  }
  return y;
}

int sumSeq2(int low, int high) {
  if (low < high) {
    int s = 0;
    for (int x = low; x < high; x++) {
      s = s + seq2(x);
    }
    return s;
  }
  return 0;
}
int main(void) {
  for (int i = -10; i <= 15; i++) {
    printf("seq2(%d) = %d\n", i, seq2(i));
  }

  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 100, 102, sumSeq2(100, 102));
  printf("sumSeq2(%d, %d) = %d\n", 1, -1, sumSeq2(1, -1));
  printf("sumSeq2(%d, %d) = %d\n", 0, 0, sumSeq2(0, 0));

  return EXIT_SUCCESS;
}
