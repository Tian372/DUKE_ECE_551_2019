#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  printf("initialize count");
  counts_t * out = malloc(sizeof(*out));
  out->array = NULL;
  out->sz = 0;
  out->unknowns = 0;
  printf("Finish initializing. size = 0");
  return out;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int flag = 0;
  one_count_t * p;
  if (name == NULL) {
    c->unknowns++;
    return;
  }
  for (size_t i = 0; i < c->sz; i++) {
    p = &c->array[i];
    if (strcmp(p->key, name) == 0) {
      p->freq++;
      flag = 1;
    }
  }
  if (flag == 0) {
    c->array = realloc(c->array, (c->sz + 1) * sizeof c->array[0]);
    p = &c->array[c->sz++];
    p->key = strdup(name);
    p->freq = 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  size_t i;
  one_count_t * p;

  for (i = 0; i < c->sz; i++) {
    p = &c->array[i];
    fprintf(outFile, "%s: %d\n", p->key, (int)p->freq);
  }
  if (c->unknowns > 0) {
    fprintf(outFile, "<unknown> : %d\n", (int)c->unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  size_t i;
  one_count_t * p;

  for (i = 0; i < c->sz; i++) {
    p = &c->array[i];
    free(p->key);
  }
  free(c->array);
  free(c);
}
