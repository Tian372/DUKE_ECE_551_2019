#ifndef __Define__
#define __Define__

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Expr.h"
#include "Functions.h"
#include "Test.h"
using namespace std;

void trimSpace(string & line);
string parseCommand(string & line);
string parseWord(string & line);
void parseDefine(string & line, map<string, Function *> & functions);

#endif
