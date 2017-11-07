#include <iostream>
#include "queue.h"
#include "squeue.cpp"
#include "lqueue.cpp"

template <typename T>
//using TestQueue = SQueue<T>;
using TestQueue = LQueue<T>;

#include "queue-tests.h"

int main() {
  RunTests();
  return 0;
}
