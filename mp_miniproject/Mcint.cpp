#include "Mcint.h"
using namespace std;

void parseMcint(string & line, map<string, Function *> & functions) {
  vector<string> str;
  vector<double> para;
  while (!line.empty()) {
    str.push_back(parseWord(line));
  }

  string id = str[0];
  if (functions.find(id) == functions.end()) {
    cout << "function " << id << " is not defined" << endl;
    return;
  }
  Function * fn = functions[id];
  size_t dim = fn->NumOfVars();
  if (str.size() - 1 != 2 * dim + 1) {
    cout << "input argument dont match function " << id << endl;
  }
  int step;

  try {
    step = stoi(str[1]);
  }
  catch (std::invalid_argument) {
    std::cerr << "num should be integer"
              << "\n";
    return;
  }

  if (step <= 0) {
    cout << "step has to be positive" << endl;
    return;
  }

  for (vector<string>::iterator it = str.begin() + 2; it != str.end(); it++) {
    if (!isNumber(*it)) {
      cout << "parameters need to be numbers" << endl;
      return;
    }
    para.push_back(stod(*it));
  }

  vector<vector<double> > boundaries;

  size_t i = 1;
  vector<double> temp;
  for (vector<double>::iterator it = para.begin(); it != para.end(); ++it) {
    if (i % 2 == 1) {
      temp.push_back(*it);
    }
    else {
      temp.push_back(*it);
      boundaries.push_back(temp);
      temp.clear();
    }
    i++;
  }

  for (size_t t = 0; t < boundaries.size(); ++t) {
    if (boundaries[t][1] - boundaries[t][0] <= 0) {
      cout << "upper bound needs to be larger than the lower" << endl;
      return;
    }
  }

  srand((unsigned)time(NULL));
  double ans = 0;
  string var;
  string temp_f;

  for (size_t i = 0; i < (size_t)step; i++) {
    for (size_t j = 0; j < dim; j++) {
      double rNum =
          ((double)rand() / (RAND_MAX)) * (boundaries[j][1] - boundaries[j][0]) +
          boundaries[j][0];
      var += " " + to_string(rNum);
    }

    temp_f = id + var + ")";

    var.clear();
    try {
      ans += evalFn(temp_f, functions);
    }
    catch (logb_Invalid_Input & e) {
      cerr << e.what() << endl;
      return;
    }
    catch (invalid_argument & e) {
      cerr << e.what() << endl;
      return;
    }
  }
  ans = ans / step;
  for (size_t j = 0; j < dim; j++) {
    ans *= (boundaries[j][1] - boundaries[j][0]);
  }

  cout << "Mcint: Integral of " << id << " = " << ans << "\n";
}
