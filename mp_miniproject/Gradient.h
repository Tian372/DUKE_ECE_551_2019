#ifndef __Gradient__
#define __Gradient__
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Define.h"
#include "Expr.h"
#include "Functions.h"
#include "Numint.h"
#include "Test.h"

using namespace std;
vector<double> doGrad(vector<double> points,
                      map<string, Function *> functions,
                      string id);
void parseGradient(string & command, string & line, map<string, Function *> & functions);
#endif
