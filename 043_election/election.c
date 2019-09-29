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
  unsigned int ev = 0;

  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > 0.5 * stateData[i].population) {
      ev = ev + stateData[i].electoralVotes;
    }
  }

  return ev;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double percent = 0;
  double pop = 0;
  double vc = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > 0.495 * stateData[i].population &&
        voteCounts[i] < 0.505 * stateData[i].population) {
      pop = stateData[i].population;
      vc = voteCounts[i];
      percent = vc * 100 / pop;
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percent);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double percent = 0.0;
  double pop = 0.0;
  double vc = 0.0;
  double largest_p = 0.0;

  size_t index_L = 0;

  for (size_t i = 0; i < nStates; i++) {
    pop = stateData[i].population;
    vc = voteCounts[i];
    percent = 100 * vc / pop;
    if (largest_p < percent) {
      index_L = i;
      largest_p = percent;
    }
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", stateData[index_L].name, largest_p);
}
