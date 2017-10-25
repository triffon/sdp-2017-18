#include <iostream>
#include <string>
#include <sstream>
#include "lstack.cpp"

#include "arithmetic.h"
#include "arithmetic_tests.h"


double Arithmetic::calculateRPN(std::string rpn) {
  std::istringstream rpns(rpn);
  RPNCalculator rpnc;
  char c;
  while(rpns >> c)
    rpnc << c;
  return rpnc.result();
}

std::string Arithmetic::toRPN(std::string expr) {
  std::istringstream exprs(expr);
  std::ostringstream rpns;
  RPNConverter<> rpnc(rpns);
  char c;
  while (exprs >> c)
    rpnc << c;

  rpnc.flush();
  
  return rpns.str();
}

double Arithmetic::calculateExpr(std::string expr) {
  //  return calculateRPN(toRPN(expr));
  std::istringstream exprs(expr);
  char c;
  while (exprs >> c)
    *this << c;
  rpnconv.flush();
  return result();
}


int main() {

  RunTests();

  Arithmetic ar;
  char c;
  while (std::cin >> c) {
    ar << c;
    std::cout << ar.result();
  }
  
  return 0;
}
