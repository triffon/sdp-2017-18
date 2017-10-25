#include <cmath>
#include "rpn_calculator.h"

void RPNCalculator::applyOperation(char op) {
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

void RPNCalculator::consumeChar(char c) {
  if (std::isdigit(c))
    stack.push(toDigit(c));
  else
    applyOperation(c);
}
