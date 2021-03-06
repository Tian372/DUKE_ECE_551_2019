#ifndef __Functions__
#define __Functions__
#include <float.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Function {
 private:
  string function_def;
  map<string, double> vars;

 public:
  Function();
  Function(string s, map<string, double> v);
  Function(const Function & rhs);

  Function & operator=(const Function & rhs);
  string getFunction();
  size_t NumOfVars();
  bool hasVar(string name);
  void setVars(vector<double> values);
  void setVar(string name, double value);
  map<string, double> getVars();

  ~Function();
};

bool isNumber(string & line);

bool isMatch(string & line);

#endif
