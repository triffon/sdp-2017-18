#ifndef _RPN_CALCULATOR
#define _RPN_CALCULATOR

#include "lstack.cpp"

class RPNCalculator {
private:
  
  using NumberStack = LinkedStack<double>;

  NumberStack stack;
  
  int toDigit(char c) {
    return c - '0';
  }

  void applyOperation(char op);

  void consumeChar(char c);

public:

  friend RPNCalculator& operator<<(RPNCalculator& rpnc, char c) {
    rpnc.consumeChar(c);
    return rpnc;
  }

  double result() const { return stack.peek(); }

};

#endif
