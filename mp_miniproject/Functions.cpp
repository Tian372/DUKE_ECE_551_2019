
#include "Functions.h"
using namespace std;

Function::Function() : function_def(NULL), vars() {
}
Function::Function(string s, map<string, double> v) : function_def(s), vars(v) {
}
Function::Function(const Function & rhs) :
    function_def(rhs.function_def),
    vars(rhs.vars) {
}
Function & Function::operator=(const Function & rhs) {
  if (this != &rhs) {
    vars.clear();
    function_def.clear();

    function_def = rhs.function_def;
    vars = rhs.vars;
  }

  return *this;
}
string Function::getFunction() {
  return function_def;
}
size_t Function::NumOfVars() {
  return vars.size();
}
bool Function::hasVar(string name) {
  return vars.find(name) != vars.end();
}
void Function::setVars(vector<double> values) {
  size_t i = 0;
  for (map<string, double>::iterator it = vars.begin(); it != vars.end(); ++it) {
    it->second = values[i];
    i++;
  }
}
void Function::setVar(string name, double value) {
  vars[name] = value;
}
map<string, double> Function::getVars() {
  return vars;
}
Function::~Function() {
}

bool isNumber(string & line) {
  char * end = 0;
  double num = strtod(line.c_str(), &end);
  return end != line.c_str() && *end == '\0' && num != DBL_MAX;
}

bool isMatch(string & line) {
  int left = count(line.begin(), line.end(), '(');
  int right = count(line.begin(), line.end(), ')');
  if (left == right) {
    return true;
  }
  else {
    return false;
  }
}

size_t split_test(string & line) {
  size_t len = line.size();
  size_t count = 0;
  int count_l = 0;
  int count_r = 0;
  for (size_t i = 0; i < len; i++) {
    if (line[i] == '(') {
      count_l++;
    }
    if (line[i] == ')') {
      count_r++;
    }
    count++;
    if (count_l == count_r) {
      break;
    }
  }
  return count;
}
