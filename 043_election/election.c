#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  char * p = strdup(line);
  state_t state;
  char *name, *cpop, *cnum;

  name = strsep(&p, ":");
  cpop = strsep(&p, ":");
  cnum = strsep(&p, ":");

  size_t name_len = strlen(name);
  int pop = atoi(cpop);
  int num = atoi(cnum);

  memcpy(state.name, name, name_len);
  state.name[name_len] = '\0';

  state.population = pop;
  state.electoralVotes = num;

  return state;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
