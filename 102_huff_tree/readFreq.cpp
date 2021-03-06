#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream input;
  input.open(fname);
  if (input.fail()) {
    fprintf(stderr, "could not open the file");
    exit(EXIT_FAILURE);
  }
  uint64_t * count = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    count[i] = 0;
  }
  int c;
  while ((c = input.get()) != EOF) {
    count[c]++;
  }
  count[256] = 1;
  input.close();
  return count;
}
