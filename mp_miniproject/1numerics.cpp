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
        cout << "define: " << endl;
        parseDefine(line, functions);
      }
      else if (command == "test") {
        cout << "test: " << endl;
        parseTest(line, functions);
      }

      else if (command == "numint") {
        cout << "numint: " << endl;
        parseNumint(line, functions);
      }
      else if (command == "mcint") {
        cout << "mcint: " << endl;
        parseMcint(line, functions);
      }
      else if (command == "max" || command == "min") {
        cout << command << ": " << endl;
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
