#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fkey) {
  //WRITE ME
  FILE * f = fopen(fkey, "r");
  kvarray_t * arr;
  arr = malloc(sizeof(*arr));
  arr->pairs = malloc(sizeof(*arr->pairs));
  arr->n = 0;
  arr->pairs[arr->n].key = NULL;
  arr->pairs[arr->n].value = NULL;
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 1;
  int flag = 0;
  int len1 = 0;
  int len2 = 0;

  while ((len = getline(&line, &sz, f)) >= 0) {
    len1 = 0;
    len2 = 0;
    flag = 0;

    for (int i = 0; i < len - 1; i++) {
      if (line[i] == '=' && flag == 0) {
        flag = 1;
      }
      else {
        if (flag == 0) {
          len1++;
          arr->pairs[arr->n].key =
              realloc(arr->pairs[arr->n].key, (i + 1) * sizeof(char));
          arr->pairs[arr->n].key[i] = line[i];
        }
        if (flag == 1) {
          len2++;
          arr->pairs[arr->n].value =
              realloc(arr->pairs[arr->n].value, (len2) * sizeof(char));
          arr->pairs[arr->n].value[len2 - 1] = line[i];
        }
      }
    }
    arr->n++;
    arr->pairs = realloc(arr->pairs, (arr->n + 1) * sizeof(*arr->pairs));
  }

  return arr;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i <= pairs->n - 1; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}
void printKVs(kvarray_t * pairs) {
  //WRITE ME

  for (size_t i = 0; i < pairs->n; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

int checkEqual(const char * str1, const char * str2) {
  const char * p = str1;
  const char * q = str2;
  while (*p == *q) {
    if (*p == '\0') {
      return 1;
    }
    p++;
    q++;
  }
  return 0;
}
char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i <= pairs->n - 1; i++) {
    if (checkEqual(pairs->pairs[i].key, key)) {
      char * out = strdup(pairs->pairs[i].value);
      return out;
    }
  }
  return NULL;
}
