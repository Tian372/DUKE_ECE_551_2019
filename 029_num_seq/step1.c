
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
    for (int i = -1; i >= x; i--) {
      out = out - 4;
    }
  }

  return out;
}

void printSeq1Range(int low, int high) {
  printf("printSeq1Range(%d, %d)\n", low, high);
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high; i++) {
      int x = seq1(i);

      printf("%d", x);
      if (i < high - 1) {
        printf(", ");
      }
    }
    printf("\n");
  }
}

int main(void) {
  for (int i = -5; i <= 11; i++) {
    printf("seq1(%d) = %d\n", i, seq1(i));
  }
  printSeq1Range(0, 0);
  printSeq1Range(100, 100);
  printSeq1Range(100, -100);
  printSeq1Range(0, 4);
  printSeq1Range(-2, 6);
  printSeq1Range(-20, 20);
}
