#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "lstack.cpp"

#include "arithmetic.h"
#include "arithmetic_tests.h"

void Arithmetic::applyOperation(char op) {
  double rarg = stack.pop();
  double larg = stack.pop();
  double result = 0;
  switch (op) {
  case '+' : result = larg + rarg;break;
  case '-' : result = larg - rarg;break;
  case '*' : result = larg * rarg;break;
  case '/' : result = larg / rarg;break;
  case '^' : result = pow(larg, rarg);
  }
  stack.push(result);
}

double Arithmetic::calculateRPN(std::string rpn) {
  std::istringstream rpns(rpn);
  char c;
  while(rpns >> c) {
    if (isDigit(c))
      stack.push(toDigit(c));
    else
      applyOperation(c);
  }
  return stack.pop();
}

std::string Arithmetic::toRPN(std::string expr) {
  std::istringstream exprs(expr);
  std::ostringstream rpns;
  char c;
  while (exprs >> c) {
    if (isDigit(c))
      rpns << c;
    else if (c == ')') {
      // изваждаме всички операции до първа отваряща скоба
      // и ги прехвърляме в резултата
      while (opstack.peek() != '(')
        rpns << opstack.pop();
      // премахваме и отварящата скоба
      opstack.pop();
    }
    else if (c == '(')
      opstack.push(c);
    else {
      // преди да сложим операцията, трябва да извадим всички операции
      // с приоритет по-висок или равен на нейния
      while (!opstack.empty() &&
             priority(opstack.peek()) >= priority(c))
        rpns << opstack.pop();
      opstack.push(c);
    }
  }

  while (!opstack.empty())
    rpns << opstack.pop();

  return rpns.str();
}

double Arithmetic::calculateExpr(std::string expr) {
  return calculateRPN(toRPN(expr));
}

int main() {

  RunTests();
  
  return 0;
}
