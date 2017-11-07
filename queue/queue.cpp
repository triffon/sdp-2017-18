#include <iostream>
#include "queue.h"
#include "squeue.cpp"

template <typename T>
using TestQueue = SQueue<T>;

#include "queue-tests.h"

int main() {
  RunTests();
  return 0;
}
