#include <iostream>
#include <cmath>
#include "queue.h"
#include "squeue.cpp"
#include "lqueue.cpp"

template <typename T>
//using TestQueue = SQueue<T>;
using TestQueue = LQueue<T>;

#include "queue-tests.h"

void dequeueIfEqual(LQueue<int>& q, int h) {
  if (q.head() == h)
    q.dequeue();
}


void printHamming(int n) {
  LQueue<int> q2, q3, q5;
  int h = 1;
  for(int i = 0; i < n; i++) {
    // извеждаме числото
    std::cout << h << ' ';

    // добавяме в опашките новите числа
    q2.enqueue(2 * h);
    q3.enqueue(3 * h);
    q5.enqueue(5 * h);

    // подготвяме следващото число
    h = std::min(q2.head(),
        std::min(q3.head(),
                 q5.head()));

    // премахваме числото от опашките
    dequeueIfEqual(q2, h);
    dequeueIfEqual(q3, h);
    dequeueIfEqual(q5, h);
  }
}

int main() {
  RunTests();

  printHamming(30);
  return 0;
}
