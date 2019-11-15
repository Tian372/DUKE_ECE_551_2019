#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);
  //WRITE YOUR CODE HERE!
  std::ifstream fin;
  fin.open(inFile);
  //open the fin file for reading
  if (fin.fail()) {
    perror("could not open file");
    exit(EXIT_FAILURE);
  }
  //You need to read the fin file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  std::map<unsigned, BitString>::const_iterator it;
  int c;
  while ((c = fin.get()) != EOF) {
    it = theMap.find((unsigned)c);
    if (it == theMap.end()) {
      perror("shuold contain c");
      exit(EXIT_FAILURE);
    }
    bfw.writeBitString(it->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  it = theMap.find(256);
  if (it == theMap.end()) {
    perror("shuold contain c");
    exit(EXIT_FAILURE);
  }
  else {
    bfw.writeBitString(it->second);
  }

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your fin file.
  fin.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress fin output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree(counts);
  delete[] counts;
  BitString empty;
  std::map<unsigned, BitString> theMap;
  tree->buildMap(empty, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete tree;
  return EXIT_SUCCESS;
}
