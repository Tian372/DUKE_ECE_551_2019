#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t x;
  size_t max = 0;

  x = 0;

  for (size_t y = 1; y <= n; y++) {
    if (y == n || array[y] <= array[y - 1]) {
      if (y - x > max) {
        max = y - x;
      }
      x = y;
    }
  }
  return max;
}
