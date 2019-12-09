#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <string>

using namespace std;
#include <time.h>

#include "Define.h"
#include "Expr.h"
#include "Functions.h"
#include "Gradient.h"
#include "Mcint.h"
#include "Numint.h"
#include "Test.h"

int main() {
  string line;
  map<string, Function *> functions;
  ifstream file("Testing.txt");

  clock_t rawtime;
  rawtime = clock();

  while (getline(file, line)) {
    if (line.empty()) {
      cout << "input is empty" << endl;
    }
    else {
      string command = parseCommand(line);

      if (command == "define") {
        parseDefine(line, functions);
      }
      else if (command == "test") {
        parseTest(line, functions);
      }

      else if (command == "numint") {
        parseNumint(line, functions);
      }
      else if (command == "mcint") {
        parseMcint(line, functions);
      }
      else if (command == "max" || command == "min") {
        parseGradient(command, line, functions);
      }
      else {
        cout << "Invade command: " << command << ". please enter another one" << endl;
      }
    }
    line.clear();
  }
  for (map<string, Function *>::iterator it = functions.begin(); it != functions.end();
       ++it) {
    delete it->second;
  }
  cout << " " << endl;
  cout << "Time taken: " << (clock() - rawtime) / CLOCKS_PER_SEC << " sec" << endl;
  return EXIT_SUCCESS;
}
