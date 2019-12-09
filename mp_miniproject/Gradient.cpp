#include "Gradient.h"
using namespace std;

vector<double> doGrad(vector<double> points,
                      map<string, Function *> functions,
                      string id) {
  string temp_f1;
  string temp_f2;
  vector<double> tempP = points;
  vector<double> grad = points;
  double step_size = 0.0001;

  for (size_t i = 0; i < tempP.size(); ++i) {
    temp_f1 = id + " " + vNumtoString(tempP) + ")";
    double f1 = evalFn(temp_f1, functions);

    tempP[i] += step_size;

    temp_f2 = id + " " + vNumtoString(tempP) + ")";

    double f2 = evalFn(temp_f2, functions);

    grad[i] = (f2 - f1) / step_size;

    tempP[i] -= step_size;
  }

  return grad;
}
void parseGradient(string & command, string & line, map<string, Function *> & functions) {
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

  str.erase(str.begin());
  Function * fn = functions[id];

  if (str.size() != (fn->NumOfVars() + 3)) {
    cout << "input argument dont match function " << id << endl;
    return;
  }
  size_t steps = stoi(str[str.size() - 1]);
  str.pop_back();

  for (vector<string>::iterator it = str.begin(); it != str.end(); it++) {
    if (!isNumber(*it)) {
      cout << "parameters need to be numbers" << endl;
      return;
    }
    para.push_back(stod(*it));
  }

  if (para[0] <= 0) {
    cout << "step size has to be positive" << endl;
    return;
  }

  double gamma = para[0];
  double convergedDistance = para[1];
  vector<double> startingP;

  for (vector<double>::iterator it = para.begin() + 2; it != para.end(); ++it) {
    startingP.push_back(*it);
  }

  //min gamma coverged <startingP> steps
  //pnew = pcurr + gamma*Df(pcurr)

  size_t k = 0;
  trimSpace(command);
  vector<double> grad = startingP;

  while (k <= steps) {
    try {
      grad = doGrad(startingP, functions, id);
    }
    catch (logb_Invalid_Input & e) {
      cerr << e.what() << endl;
      return;
    }
    catch (invalid_argument & e) {
      cerr << e.what() << endl;
      return;
    }
    for (size_t i = 0; i < grad.size(); ++i) {
      if (command == "min") {
        if (abs(grad[i]) <= convergedDistance) {
          grad[i] = 0;
        }

        startingP[i] -= gamma * grad[i];
      }
      else if (command == "max") {
        if (abs(grad[i]) <= convergedDistance) {
          grad[i] = 0;
        }
        startingP[i] += gamma * grad[i];
      }
    }
    ++k;
  }

  for (size_t i = 0; i < startingP.size(); ++i) {
    if (abs(startingP[i]) <= convergedDistance) {
      startingP[i] = 0;
    }
    else if (ceil(startingP[i]) - startingP[i] <= convergedDistance) {
      startingP[i] = ceil(startingP[i]);
    }
    else if (startingP[i] - floor(startingP[i]) <= convergedDistance) {
      startingP[i] = floor(startingP[i]);
    }
  }
  cout.precision(8);

  cout << "(" << startingP[0] << ", ";
  for (size_t i = 1; i < startingP.size() - 1; ++i) {
    cout << startingP[i] << ", ";
  }
  cout << startingP[startingP.size() - 1] << ")" << endl;
}
