#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseLine(kvpair_t * pair, const char * line) {
  const char *p, *q;
  p = strchr(line, '=');

  pair->key = strndup(line, (size_t)(p - line));
  q = strchr(++p, '\n');

  pair->value = strndup(p, (size_t)(q - p));
}

kvarray_t * readKVs(const char * fname) {
  FILE * f;
  char * line = NULL;
  size_t linesz = 0;
  kvpair_t * pair = 0;
  size_t n = 0;
  kvarray_t * arr;

  f = fopen(fname, "r");
  while (getline(&line, &linesz, f) != -1) {
    pair = realloc(pair, (n + 1) * sizeof *pair);
    parseLine(&pair[n++], line);
  }
  free(line);
  fclose(f);

  arr = malloc(sizeof *arr);

  arr->pairs = pair;
  arr->n = n;
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
  size_t i;
  kvpair_t * p;

  for (i = 0; i < pairs->n; i++) {
    p = &pairs->pairs[i];
    printf("key = '%s' value = '%s'\n", p->key, p->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t i;
  kvpair_t * p;

  for (i = 0; i < pairs->n; i++) {
    p = &pairs->pairs[i];
    if (!strcmp(key, p->key)) {
      return p->value;
    }
  }
  return NULL;
}
