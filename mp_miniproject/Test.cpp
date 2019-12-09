#include "Test.h"
using namespace std;

bool isValidOp(string & op) {
  trimSpace(op);
  if (op == "+") {
    return true;
  }
  else if (op == "-") {
    return true;
  }
  else if (op == "*") {
    return true;
  }
  else if (op == "/") {
    return true;
  }
  else if (op == "%") {
    return true;
  }
  else if (op == "sqrt") {
    return true;
  }
  else if (op == "pow" || op == "^") {
    return true;
  }
  else if (op == "floor") {
    return true;
  }
  else if (op == "ceil") {
    return true;
  }
  else if (op == "round") {
    return true;
  }
  else if (op == "logb") {
    return true;
  }
  else if (op == "select") {
    return true;
  }
  else {
    cout << "Impossible op: " << op << "\n";
    return false;
  }
}
size_t Operands(string & op) {
  if (op == "+") {
    return 2;
  }
  else if (op == "-") {
    return 2;
  }
  else if (op == "*") {
    return 2;
  }
  else if (op == "/") {
    return 2;
  }
  else if (op == "%") {
    return 2;
  }
  else if (op == "sqrt") {
    return 1;
  }
  else if (op == "pow" || op == "^") {
    return 2;
  }
  else if (op == "floor") {
    return 1;
  }
  else if (op == "ceil") {
    return 1;
  }
  else if (op == "round") {
    return 1;
  }
  else if (op == "logb") {
    return 2;
  }
  else if (op == "select") {
    return 3;
  }
  else {
    return 0;
  }
}
Expression * makeExpr(string & op, Expression * lhs, Expression * rhs, Expression * e3) {
  trimSpace(op);
  if (op == "+") {
    return new PlusExpression(lhs, rhs);
  }
  else if (op == "-") {
    return new MinusExpression(lhs, rhs);
  }
  else if (op == "*") {
    return new TimesExpression(lhs, rhs);
  }
  else if (op == "/") {
    return new DivExpression(lhs, rhs);
  }
  else if (op == "%") {
    return new ModExpression(lhs, rhs);
  }
  else if (op == "pow" || op == "^") {
    return new PowExpression(lhs, rhs);
  }
  else if (op == "sqrt") {
    return new SqrtExpression(lhs);
  }
  else if (op == "floor") {
    return new floorExpression(lhs);
  }
  else if (op == "ceil") {
    return new ceilExpression(lhs);
  }
  else if (op == "round") {
    return new roundExpression(lhs);
  }
  else if (op == "logb") {
    if (lhs->evaluate() <= 0 || rhs->evaluate() <= 0) {
      throw(logb_Invalid_Input("Operands for logb should be postive"));
    }
    return new LogbExpression(lhs, rhs);
  }
  else if (op == "select") {
    return new selectExpression(lhs, rhs, e3);
  }

  else {
    std::cerr << "Impossible op char: " << op << "\n";
    return NULL;
  }
}
Expression * parseOp(string & id, string & fn_def, map<string, double> vars) {
  string op = parseWord(fn_def);
  if (!isValidOp(op)) {
    std::cerr << "Invalid op: " << op << "\n";
    return NULL;
  }
  if (Operands(op) == 2) {
    Expression * lhs = parse(id, fn_def, vars);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = parse(id, fn_def, vars);
    if (rhs == NULL) {
      delete lhs;
      return NULL;
    }
    string temp = parseWord(fn_def);

    if (temp == ")") {
      return makeExpr(op, lhs, rhs, NULL);
    }
    cerr << "Expecting a ) but found " << temp << endl;
    delete lhs;
    delete rhs;
    return NULL;
  }

  else if (Operands(op) == 1) {
    Expression * lhs = parse(id, fn_def, vars);
    if (lhs == NULL) {
      return NULL;
    }
    string temp = parseWord(fn_def);

    if (temp == ")") {
      return makeExpr(op, lhs, NULL, NULL);
    }
    std::cerr << "Expecting ) but found " << temp << "\n";
    delete lhs;
    return NULL;
  }

  else if (Operands(op) == 3) {
    Expression * e1 = parse(id, fn_def, vars);
    if (e1 == NULL) {
      return NULL;
    }
    Expression * e2 = parse(id, fn_def, vars);
    if (e2 == NULL) {
      delete e2;
      return NULL;
    }
    Expression * e3 = parse(id, fn_def, vars);
    if (e3 == NULL) {
      delete e3;
      return NULL;
    }
    string temp = parseWord(fn_def);

    if (temp == ")") {
      return makeExpr(op, e1, e2, e3);
    }
    std::cerr << "Expecting ) but found " << temp << "\n";
    delete e1;
    delete e2;
    delete e3;
    return NULL;
  }
  else {
    cout << "<test> invalid operands number" << endl;
    return NULL;
  }
}

Expression * parse(string & id, string & fn_def, map<string, double> vars) {
  trimSpace(fn_def);
  if (fn_def.empty()) {
    std::cerr << "<test> function definition is empty" << endl;
    return NULL;
  }

  string temp = parseWord(fn_def);

  if (temp == "(") {
    // (op E E)
    return parseOp(id, fn_def, vars);
  }
  else {
    //number
    if (isNumber(temp)) {
      double num = stod(temp);
      return new NumExpression(num);
    }
    else {
      if (vars.find(temp) != vars.end()) {
        return new NumExpression(vars[temp]);
      }
      else {
        cout << "variables " << vars[temp] << " is not in function " << id << endl;
        return NULL;
      }
    }
  }
}

double evalFn(string & line, map<string, Function *> & functions) {
  string id = parseWord(line);

  if (functions.find(id) == functions.end()) {
    cout << "<test> founction " << id << " does not exits" << endl;
    return DBL_MAX;
  }

  Function * fn = functions[id];
  string fn_Def = fn->getFunction();
  vector<double> values;

  while (line[0] != ')') {
    string temp = parseWord(line);
    if (temp == "(") {
      values.push_back(evalFn(line, functions));
    }
    else {
      if (isNumber(temp)) {
        values.push_back(stod(temp));
      }
      else {
        cout << "<test> there is no number for unassigned variables " << endl;
      }
    }
  }
  line.erase(0, 1);

  if (values.size() == fn->NumOfVars()) {
    fn->setVars(values);
  }
  else {
    cout << "<test> too many arguments for function " << id << endl;
    return DBL_MAX;
  }

  Expression * expr = parse(id, fn_Def, fn->getVars());
  double ans;

  ans = expr->evaluate();

  delete expr;
  return ans;
}

void parseTest(string & line, map<string, Function *> & functions) {
  if (line.empty()) {
    cout << "<test> input is empty" << endl;
    return;
  }
  if (!isMatch(line)) {
    cout << "<test> test line does not have matched ()" << endl;
  }
  size_t bound = line.find_last_of(')');
  string result_s = line.substr(bound + 1);
  line = line.substr(0, bound + 1);

  string line2 = line;
  trimSpace(line2);
  double result;
  double ans;

  if (isNumber(result_s)) {
    result = stod(result_s);
  }
  else {
    cout << "<test> result need to be a number" << endl;
    return;
  }

  //(f (g 1 2) (g 2 5))
  string temp = parseWord(line);
  try {
    if (temp == "(") {
      ans = evalFn(line, functions);
    }
    else {
      cout << "<test> need ( to start a function evaluation" << endl;
      return;
    }
  }
  catch (logb_Invalid_Input & e) {
    cout << e.what() << endl;
    return;
  }
  catch (invalid_argument & e) {
    cerr << e.what() << endl;
    return;
  }

  if (abs(ans - result) < 0.0000000000001) {
    cout << line2 << "= " << result << " [correct]" << endl;
  }
  else {
    cout << line2 << " = " << result << " [INCORRECT: expected " << ans << "]" << endl;
  }
}
