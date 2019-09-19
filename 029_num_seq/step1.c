// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  int out = -3;

  if (x >= 0) {
    for (int i = 1; i <= x; i++) {
      out = out + 4;
    }
  }

  else {
    for (int i = -2; i >= -x; i--) {
      out = out - 4;
    }
  }

  return out;
}

int main(void) {
  for (int i = 0; i <= 20; i++) {
    int x = seq1(i);

    printf("%d\n", x);
  }

  for (int i = 4; i >= -10; i--) {
    int x = seq1(x);
    printf("%d\n", x);
  }
}
