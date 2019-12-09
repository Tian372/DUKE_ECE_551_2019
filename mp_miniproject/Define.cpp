#include "Define.h"
using namespace std;
/* "trimSpace" is used to get rid of all the empty space of the head
   and the tail of a string.
   SpcaeSpacelineSpaceSpace 
   trimSpace(line)
   line
*/
void trimSpace(string & line) {
  line.erase(0, line.find_first_not_of(" "));
  line.erase(line.find_last_not_of(" ") + 1);
}
/*pareCommand will take the first word before the first space or "("
  
 */
string parseCommand(string & line) {
  trimSpace(line);
  string str;
  size_t pos = 0;
  //looking for the first seperator "(" , ")" or "space"
  while (pos < line.size()) {
    if ((line[pos] == '(' || line[pos] == ')' || isspace(line[pos]))) {
      break;
    }
    pos++;
  }
  //second argument for substr is the length of the line is the
  if (pos == 0) {
    str = line.substr(0, 1);
    line.erase(0, 1);
    trimSpace(line);
  }
  else {
    str = line.substr(0, pos);
    trimSpace(str);
    //remove the command from the original line
    line.erase(0, pos);
    trimSpace(line);
  }

  return str;
}
/*take one word from the top of a string
  seperate by (, ) or space
*/
string parseWord(string & line) {
  trimSpace(line);
  string str;
  size_t pos = 0;

  while (pos < line.size()) {
    if (line[pos] == '(' || line[pos] == ')' || isspace(line[pos])) {
      break;
    }
    pos++;
  }
  if (pos == 0) {
    str = line.substr(0, 1);
    line.erase(0, 1);
    trimSpace(line);
  }
  else {
    str = line.substr(0, pos);
    trimSpace(str);
    //remove the command from the original line
    line.erase(0, pos);
    trimSpace(line);
  }

  return str;
}

/*parseDefine function
  input: define line, map of functions
*/
void parseDefine(string & line, map<string, Function *> & functions) {
  if (line.find("=") == string::npos) {
    cout << "cannot find =" << endl;
    return;
  }
  if (!isMatch(line)) {
    cout << "<define> Define line does not have matched parentheses" << endl;
    return;
  }
  string str1 = line.substr(0, line.find("="));
  string str2 = line.substr(line.find("=") + 1);
  //working on str1 before the =
  string id;
  map<string, double> vars;
  vector<string> str1_v;
  //compare repeatation of vars
  while (!str1.empty()) {
    str1_v.push_back(parseWord(str1));
  }
  size_t i = 1;
  if (str1_v[0] != "(") {
    cout << "<define> need to start with a (" << endl;
    return;
  }

  while (i < str1_v.size() - 1) {
    if (i == 1) {
      id = str1_v[i];

      if (functions.find(id) != functions.end()) {
        cout << "<define> error to attempt to re-define function " << id << endl;
        return;
      }
    }
    else {
      vars.insert(pair<string, double>(str1_v[i], 0.0));
    }
    i++;
  }
  if (vars.size() == 0) {
    cout << "<define> no variable can be found" << endl;
    return;
  }
  //working on str2 after "="
  trimSpace(str2);

  if (isMatch(str2)) {
    Function * function = new Function(str2, vars);
    functions.insert(pair<string, Function *>(id, function));
  }
  else {
    cout << "<define> function define line does not have matched parentheses" << endl;
    return;
  }

  cout << "defined " << id << "(";
  string display;
  for (map<string, double>::iterator it = vars.begin(); it != vars.end(); it++) {
    display += (it->first);
    display += (" ");
  }
  display.erase(display.size() - 1, display.size());
  cout << display << ")" << endl;
}
