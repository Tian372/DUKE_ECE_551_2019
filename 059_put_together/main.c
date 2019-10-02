#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f;
  char * line = NULL;
  size_t linesz = 0;
  counts_t * out;
  ssize_t read;

  f = fopen(filename, "r");
  if (f == NULL) {
    perror("cannot read file");
    exit(EXIT_FAILURE);
  }
  out = createCounts();
  while ((read = getline(&line, &linesz, f)) != -1) {
    if (read > 0 && line[read - 1] == '\n')
      line[read - 1] = '\0';
    addCount(out, lookupValue(kvPairs, line));
  }
  if (!feof(f)) {
    fprintf(stderr, "invalid input format\n");
    exit(EXIT_FAILURE);
  }
  free(line);
  fclose(f);
  return out;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv;
  int i;
  //count from 2 to argc (call the number you count i)
  if (argc < 3) {
    fprintf(stderr, "need at least three argument\n");
    exit(EXIT_FAILURE);
  }
  kv = readKVs(argv[1]);
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)
  for (i = 2; i < argc; i++) {
    counts_t * c;
    char * outName;
    //compute the output file name from argv[i] (call this outName)
    FILE * f;
    //open the file named by outName (call that f)
    c = countFile(argv[i], kv);
    //print the counts from c into the FILE f
    outName = computeOutputFileName(argv[i]);
    f = fopen(outName, "w");
    if (f == NULL) {
      perror("can't open file");
      exit(EXIT_FAILURE);
    }
    //close f
    printCounts(c, f);
    fclose(f);
    //free the memory for outName and c
    free(outName);
    //free the memory for kv
    freeCounts(c);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
