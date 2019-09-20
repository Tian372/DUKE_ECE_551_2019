// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int z = (y - 3) * x + 2 * y;

  return z;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int c = 0;

  if (xLow < xHi && yLow < yHi) {
    for (int x = xLow; x < xHi; x++) {
      for (int y = yLow; y < yHi; y++) {
        if (seq3(x, y) % 2 == 0) {
          c++;
        }
      }
    }
  }

  return c;
}

int main(void) {
  for (int i = -10; i <= 10; i++) {
    for (int k = -10; k <= 10; k++) {
      printf("seq3(%d, %d) = %d\n", i, k, seq3(i, k));
    }
  }

  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         1,
         0,
         1,
         countEvenInSeq3Range(0, 1, 0, 1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         1,
         -1,
         1,
         countEvenInSeq3Range(-1, 1, -1, 1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -103,
         -100,
         100,
         103,
         countEvenInSeq3Range(-103, -100, 100, 103));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         -2,
         0,
         1,
         countEvenInSeq3Range(-1, -2, 0, 1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         0,
         1,
         2,
         countEvenInSeq3Range(0, 0, 1, 2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         2,
         1,
         -1,
         countEvenInSeq3Range(0, 2, 1, -1));
}
