#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  char * p = strdup(line);

  //check for the empty
  char * errcheck = strdup(line);  //copy another string for testing
  char * test_token;
  int count = 0;

  while ((test_token = strsep(&errcheck, ":")) != NULL) {
    //checking if there are 3 elements
    count++;
  }
  if (count < 3) {
    printf("There are too few columns");
    exit(EXIT_FAILURE);
  }
  else if (count > 3) {
    printf("There are too many columns");
    exit(EXIT_FAILURE);
  }

  //initiate state_t
  state_t state;
  char *name, *cpop, *cnum;
  //separate by :
  name = strsep(&p, ":");
  cpop = strsep(&p, ":");
  //converting population from string to int
  int pop = atoi(cpop);
  cnum = strsep(&p, ":");

  size_t name_len = strlen(name);

  if (name_len > MAX_STATE_NAME_LENGTH - 1) {
    printf("The name is too long");
    exit(EXIT_FAILURE);
  }
  int num = atoi(cnum);
  //copy from a pointer to array
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
  //
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
