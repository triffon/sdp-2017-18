#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#include <string>
#include "lstack.cpp"

class Arithmetic {

private:

  // typedef LinkedStack<double> NumberStack;
  using NumberStack = LinkedStack<double>;
  using OpStack     = LinkedStack<char>;

  NumberStack stack;
  OpStack opstack;
  
  bool isDigit(char c) {
    return '0' <= c && c <= '9';
  }

  int toDigit(char c) {
    return c - '0';
  }

  int priority(char op) {
    switch (op) {
    case '+':
    case '-':return 1;
    case '*':
    case '/':return 2;
    case '^':return 3;
    }
    return 0;
  }

  void applyOperation(char op);

public:

  double calculateRPN(std::string rpn);

  std::string toRPN(std::string expr);

  double calculateExpr(std::string expr);
};

#endif
