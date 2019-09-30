#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include any other headers you need here...
//struct state_tag {
//  char name[MAX_STATE_NAME_LENGTH];
//  uint64_t population;
//  unsigned int electoralVotes;
//};
//typedef struct state_tag state_t;
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
    printf("There are too few columns\n");
    exit(EXIT_FAILURE);
  }
  else if (count > 3) {
    printf("There are too many columns\n");
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
  //get the length of state names
  size_t name_len = strlen(name);
  //making sure the name is within the max length
  if (name_len > MAX_STATE_NAME_LENGTH - 1) {
    printf("The name is too long");
    exit(EXIT_FAILURE);
  }

  int num = atoi(cnum);
  //copy from a pointer to array
  memcpy(state.name, name, name_len);
  state.name[name_len] = '\0';
  //assign value to population and votes
  state.population = (unsigned int)pop;
  state.electoralVotes = num;
  //return state_t state
  return state;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  unsigned int ev = 0;
  //loop through stateDate, everytime voteCounts > 50% population
  //add the electoralVotes
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > 0.5 * stateData[i].population) {
      ev = ev + stateData[i].electoralVotes;
    }
  }

  return ev;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double percent = 0.0;
  double pop = 0.0;
  double vc = 0.0;
  //I do not know if there will be problems casting uint64 to double
  //see if the persentage of votes is bewteen 49.5% and 50.5%
  //if so, recount
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
  //loop through stateDate, looking for the larget percentage
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
