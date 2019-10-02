#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  char * out;

  out = strdup(inputName);
  out = realloc(out, (len + 8) * sizeof(*out));
  memcpy(out + len, ".counts", 8);

  return out;
}
