#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int Max(int * arr, int num) {
  int maxIdx = 0;

  for (int i = 1; i < num; i++)
    if (arr[i] > arr[maxIdx])
      maxIdx = i;

  return maxIdx;
}
int getkey(FILE * f) {
  int freq[26] = {0};
  int ch;
  int maxIdx;

  while ((ch = fgetc(f)) != EOF) {
    if (isalpha(ch)) {
      freq[tolower(ch) - 'a']++;
    }
  }
  maxIdx = Max(freq, 26);

  return (maxIdx + 22) % 26;
}

int main(int argc, char * argv[]) {
  FILE * f;
  int key;
  if (argc != 2) {
    exit(EXIT_FAILURE);
  }

  f = fopen(argv[1], "r");

  if (f == NULL) {
    exit(EXIT_FAILURE);
  }
  key = getkey(f);
  printf("%d\n", key);
  if (fclose(f) == 0) {
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
