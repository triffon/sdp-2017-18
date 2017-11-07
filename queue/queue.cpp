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

template <typename T>
T minQueue(Queue<T>& q, T const& sentinel) {
  if (q.empty())
    return T();
  
  T min = q.dequeue();
  q.enqueue(sentinel);
  while (q.head() != sentinel) {
    if (min > q.head()) {
      // нов минимум!
      q.enqueue(min);
      min = q.dequeue();
    } else
      // просто прехвърляме елемента накрая на опашката
      q.enqueue(q.dequeue());
  }
  // q.head() == sentinel, махаме сентинела
  q.dequeue();
  return min;
}

LQueue<int> sortQueue(LQueue<int> q) {
  LQueue<int> result;
  while (!q.empty())
    result.enqueue(minQueue(q, -1));
  return result;
}

void testSortQueue() {
  LQueue<int> q;
  q.enqueue(5);
  q.enqueue(6);
  q.enqueue(3);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(4);
  LQueue<int> q2 = sortQueue(q);
  q2.print();
}

int main() {
  RunTests();

  printHamming(30);
  testSortQueue();

  return 0;
}
