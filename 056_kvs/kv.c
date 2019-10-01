#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void errorExit(void) {
  perror("kv");
  exit(EXIT_FAILURE);
}

static void parseLine(kvpair_t * pair, const char * line) {
  const char *p, *q;

  p = strchr(line, '=');
  if (p == NULL) {
    goto fail;
  }

  pair->key = strndup(line, (size_t)(p - line));
  q = strchr(++p, '\n');
  if (q == NULL) {
    goto fail;
  }
  pair->value = strndup(p, (size_t)(q - p));
  if (pair->key == NULL || pair->value == NULL) {
    goto fail;
  }
  return;
fail:
  fprintf(stderr, "invalid input format\n");
  exit(EXIT_FAILURE);
}

kvarray_t * readKVs(const char * fname) {
  FILE * f;
  char * line = NULL;
  size_t linesz = 0;
  kvpair_t * pairs = 0;
  size_t npairs = 0;
  kvarray_t * arr;

  f = fopen(fname, "r");
  if (f == NULL) {
    errorExit();
  }

  while (getline(&line, &linesz, f) != -1) {
    pairs = realloc(pairs, (npairs + 1) * sizeof *pairs);
    if (pairs == NULL) {
      errorExit();
    }
    parseLine(&pairs[npairs++], line);
  }
  if (!feof(f)) {
    errorExit();
  }
  free(line);
  fclose(f);

  arr = malloc(sizeof *arr);
  if (arr == NULL) {
    errorExit();
  }
  arr->pairs = pairs;
  arr->n = npairs;
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
