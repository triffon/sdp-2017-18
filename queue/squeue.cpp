#include <iostream>
#include "queue.h"

const int MAX = 100;

template <typename T>
class SQueue : public Queue<T> {
private:
  T a[MAX];
  int front, back;

  // проверка дали опашката е запълнена
  bool full() const {
    return back == MAX - 1;
  }
  
public:

  // конструктор на празна опашка
  SQueue() : front(0), back(-1) {}
  
  // проверка за празнота на опашка
  bool empty() const {
    return front > back;
  }

  // включване на елемент на края на опашката
  bool enqueue(T const& x) {
    if (full()) {
      std::cerr << "Опит за включване в пълна опашка!\n";
      return false;
    }
      
    a[++back] = x;
    return true;
  }

  // изключване на елемент от началото на опашката
  T dequeue() {
    if (empty()) {
      std::cerr << "Опит за изключване от празна опашка!\n";
      return T();
    }

    return a[front++];
  }   

  // достъп до първия елемент на опашката
  T head() const {
    if (empty()) {
      std::cerr << "Опит за достъп до първи елемент на празна опашка!\n";
      return T();
    }

    return a[front];
  }

  // достъп до първия елемент на опашката с възможност за промяна
  T& head() {
    if (empty()) {
      std::cerr << "Опит за достъп до първи елемент на празна опашка!\n";
      return a[0];
    }

    return a[front];
  }

};
