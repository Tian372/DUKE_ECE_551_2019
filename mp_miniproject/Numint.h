#ifndef __Numint__
#define __Numint__
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <thread>

#include "Define.h"
#include "Expr.h"
#include "Functions.h"
#include "Test.h"

using namespace std;
/*
void thEvalFn(map<string, Function *> functions,
              const string id,
              vector<double> v,
              double & ans,
              double lower,
              double upper,
              const double step_size);
*/
string vNumtoString(vector<double> vars);
double Numint(const string & id,
              const double & step,
              size_t pos,
              vector<double> & iValue,
              const vector<vector<double> > & boundaries,
              map<string, Function *> & functions);
void parseNumint(string & line, map<string, Function *> & functions);

#endif
