#ifndef __Mcint__
#define __Mcint__
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Define.h"
#include "Functions.h"
#include "Expr.h"
#include "Test.h"

using namespace std;

void parseMcint(string & line, map<string, Function *> & functions);

#endif