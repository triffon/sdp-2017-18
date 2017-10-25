#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#include <string>
#include "lstack.cpp"
#include "rpn_converter.h"
#include "rpn_calculator.h"

class Arithmetic {

private:
  RPNCalculator rpncalc;
  RPNConverter rpnconv;
  
  void consumeChar(char c) {
    rpnconv << c;
  }

public:

  double calculateRPN(std::string rpn);

  std::string toRPN(std::string expr);

  double calculateExpr(std::string expr);

  friend Arithmetic& operator<<(Arithmetic& ar, char c) {
    ar.consumeChar(c);
    return ar;
  }

  Arithmetic() : rpnconv(rpncalc) {}

  double result() const {
    return rpncalc.result();
  }

};

#endif
