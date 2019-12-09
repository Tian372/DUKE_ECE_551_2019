#ifndef __Test__
#define __Test__
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

#include "Define.h"
#include "Expr.h"
#include "Functions.h"
using namespace std;
//check if the operator is a validOP return true if valid
bool isValidOp(string & op);
//return the how many Operands a valid operator has, return 1, 2 or 3 accordingly
size_t Operands(string & op);
//quote from HW85 changed the input from char* to std:;string
Expression * makeExpr(string & op, Expression * lhs, Expression * rhs, Expression * e3);
Expression * parseOp(string & id, string & fn_def, map<string, double> vars);
Expression * parse(string & id, string & fn_def, map<string, double> vars);
//evalFn return a double with given variables values
double evalFn(string & line, map<string, Function *> & functions);
//parseTest compares the given answer with the correct answer
//print [correct] if correct
//print the right answer otherwise
void parseTest(string & line, map<string, Function *> & functions);

#endif
