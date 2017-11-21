#include <iostream>
#include "queue.h"

const int MAX = 105;

template <typename T>
class SQueue : public Queue<T> {
private:
  T a[MAX];
  int front, back;

  // O(1)
  // проверка дали опашката е запълнена
  bool full() const {
    return (back + 2) % MAX == front;
  }
  
public:

  // O(1)
  // конструктор на празна опашка
  SQueue() : front(0), back(-1) {}

  // O(1)
  // проверка за празнота на опашка
  bool empty() const {
    return (back + 1) % MAX == front;
  }

  // O(1)
  // включване на елемент на края на опашката
  bool enqueue(T const& x) {
    if (full()) {
      std::cerr << "Опит за включване в пълна опашка!\n";
      return false;
    }

    a[++back %= MAX] = x;
    return true;
  }

  // O(1)
  // изключване на елемент от началото на опашката
  T dequeue() {
    if (empty()) {
      std::cerr << "Опит за изключване от празна опашка!\n";
      return T();
    }

    T const& x = a[front++];
    front %= MAX;
    return x;
  }   

  // O(1)
  // достъп до първия елемент на опашката
  T head() const {
    if (empty()) {
      std::cerr << "Опит за достъп до първи елемент на празна опашка!\n";
      return T();
    }

    return a[front];
  }

  // O(1)
  // достъп до първия елемент на опашката с възможност за промяна
  T& head() {
    if (empty()) {
      std::cerr << "Опит за достъп до първи елемент на празна опашка!\n";
      return a[0];
    }

    return a[front];
  }

};
