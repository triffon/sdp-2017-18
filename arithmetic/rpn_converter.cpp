#include "rpn_converter.h"

void RPNConverter::consumeChar(char c) {
  if (std::isdigit(c))
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

void RPNConverter::flush() {
  while (!opstack.empty())
    rpns << opstack.pop();
}
