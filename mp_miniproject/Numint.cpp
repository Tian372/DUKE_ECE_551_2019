#include "Numint.h"

using namespace std;

string vNumtoString(vector<double> vars) {
  string str;
  for (size_t i = 0; i < vars.size() - 1; i++) {
    str = str + to_string(vars[i]) + " ";
  }
  str = str + to_string(vars[vars.size() - 1]);
  return str;
}
/*
void thEvalFn(map<string, Function *> functions,
              const string id,
              vector<double> v,
              double & ans,
              double lower,
              double upper,
              const double step_size) {
  string temp_f;
  double temp_ans = 0;
  for (double ls = lower; ls < upper; ls += step_size) {
    temp_f = id + " " + vNumtoString(v) + ")";
    temp_ans += abs(evalFn(temp_f, functions));
  }
  ans += temp_ans;
}
*/
/*
void theTop(const string id,
            const double step,
            size_t pos,
            vector<double> iValue,
            vector<vector<double> > boundaries,
            map<string, Function *> functions,
            double & ans,
            double upper,
            double lower) {
  double temp = 0;
  for (double ls = lower; ls <= upper; ls += step) {
    iValue[pos] = ls;
    temp += Numint(id, step, pos + 1, iValue, boundaries, functions);
  }
  ans += temp;
  }*/
double Numint(const string & id,
              const double & step,
              size_t pos,
              vector<double> & iValue,
              const vector<vector<double> > & boundaries,
              map<string, Function *> & functions) {
  double ans = 0;
  string temp_f;

  if (pos == iValue.size() - 1) {
    for (double ls = boundaries[pos][0]; ls <= boundaries[pos][1]; ls += step) {
      iValue[pos] = ls;
      temp_f = id + " " + vNumtoString(iValue) + ")";
      ans += abs(evalFn(temp_f, functions));
    }

    /*
    vector<thread> threads;
    double gap = boundaries[pos][1] - boundaries[pos][0];
    gap /= 10;
    double lower = boundaries[pos][0];

    for (size_t i = 0; i <= 10; i++) {
      threads.push_back(
          thread(thEvalFn, functions, id, iValue, ref(ans), lower, lower + gap, step));
      lower += gap;
    }
    for (size_t i = 0; i <= 10; i++) {
      threads[i].join();
    }
    */
  }
  /* else if (pos == 0) {
    vector<thread> threads;
    double gap = boundaries[pos][1] - boundaries[pos][0];
    gap /= 10;
    double lower = boundaries[pos][0];

    for (size_t i = 0; i <= 10; i++) {
      threads.push_back(thread(theTop,
                               id,
                               step,
                               pos,
                               iValue,
                               boundaries,
                               functions,
                               ref(ans),
                               lower + gap,
                               lower));
      lower += gap;
    }
    for (size_t i = 0; i <= 10; i++) {
      threads[i].join();
    }
    }*/

  else {
    for (double ls = boundaries[pos][0]; ls <= boundaries[pos][1]; ls += step) {
      iValue[pos] = ls;
      ans += Numint(id, step, pos + 1, iValue, boundaries, functions);
    }
  }

  return ans;
}
void parseNumint(string & line, map<string, Function *> & functions) {
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
  if (str.size() - 1 != 2 * (fn->NumOfVars()) + 1) {
    cout << "input argument dont match function " << id << endl;
    return;
  }
  for (vector<string>::iterator it = str.begin() + 1; it != str.end(); it++) {
    if (!isNumber(*it)) {
      cout << "parameters need to be numbers" << endl;
      exit(EXIT_FAILURE);
    }
    para.push_back(stod(*it));
  }

  if (para[0] <= 0) {
    cout << "step size has to be positive" << endl;
    return;
  }

  double step = para[0];

  vector<vector<double> > boundaries;

  size_t i = 1;
  vector<double> temp;
  for (vector<double>::iterator it = para.begin() + 1; it != para.end(); ++it) {
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
    if (boundaries[t][1] - boundaries[t][0] < step) {
      cout << "step size need to be not greater than the range" << endl;
      return;
    }
  }

  vector<double> iValue;
  for (size_t t = 0; t < boundaries.size(); ++t) {
    if (boundaries[t][1] - boundaries[t][0] <= 0) {
      cout << "upper bound needs to be larger than the lower" << endl;
      return;
    }
    else {
      iValue.push_back(boundaries[t][0]);
    }

    if (boundaries[t][1] - boundaries[t][0] < step) {
      cout << "step size need to be not greater than the range" << endl;
      return;
    }
  }

  size_t pos = 0;
  double ans = 0;
  string temp_f;
  try {
    ans = Numint(id, step, pos, iValue, boundaries, functions) *
          pow(step, boundaries.size());
  }
  catch (logb_Invalid_Input & e) {
    cerr << e.what() << endl;
    return;
  }
  catch (invalid_argument & e) {
    cerr << e.what() << endl;
    return;
  }

  cout << "Numint: integral of " << id << " = " << ans << endl;
}
