#include <iostream>
#include "queue.h"

template <typename T>
struct QueueElement {

  QueueElement(T const& _data, QueueElement* _next = nullptr) :
    data(_data), next(_next) {}

  T data;
  QueueElement* next;
};

template <typename T>
class LQueue : public Queue<T> {
private:
  QueueElement<T> *front, *back;

  T error;
  
  // O(n) по време, O(1) по памет
  void copy(LQueue const& q) {
    QueueElement<T>* p = q.front;
    while (p != nullptr) {
      enqueue(p->data);
      p = p->next;
    }
  }

  // O(n)
  void clean() {
    while (!empty())
      dequeue();
  }


public:
  // O(1)
  // конструиране на празна опашка
  LQueue() : front(nullptr), back(nullptr) {}

  // конструктор за копиране
  LQueue(LQueue const& q) : front(nullptr), back(nullptr) {
    copy(q);
  }

  // операция за присвояване
  LQueue& operator=(LQueue const& q) {
    if (this != &q) {
      clean();
      copy(q);
    }
    return *this;
  }

  // деструктор
  ~LQueue() {
    clean();
  }

  // O(1)
  // проверка за празнота на опашка
  bool empty() const {
    return back == nullptr;
  }

  // O(1)
  // включване на елемент на края на опашката
  bool enqueue(T const& x) {
    QueueElement<T>* p = new QueueElement<T>(x);
    if (back != nullptr)
      // опашката не е празна, завързваме края за новия край
      back->next = p;
    else
      // опашката е празна, насочваме front да сочи към първата клетка
      front = p;
    back = p;
    return true;
  }

  // O(1)
  // изключване на елемент от началото на опашката
  T dequeue() {
    if (empty()) {
      std::cerr << "Опит за изключване от празна опашка!\n";
      return T();
    }

    T x = front->data;
    QueueElement<T>* p = front;
    front = p->next;
    if (front == nullptr)
      back = nullptr;
    delete p;
    return x;
  }

  // O(1)
  // достъп до първия елемент на опашката
  T head() const {
    if (empty()) {
      std::cerr << "Опит за достъп до началото на празна опашка!\n";
      return error;
    }

    return front->data;
  }

  // O(1)
  // достъп до първия елемент на опашката с възможност за промяна
  T& head() {
    if (empty()) {
      std::cerr << "Опит за достъп до началото на празна опашка!\n";
      return error;
    }

    return front->data;
  }

  // O(n) по време и по памет
  void print(std::ostream& os = std::cout) const {
    LQueue<T> copy = *this;
    while (!copy.empty())
      os << copy.dequeue() << ' ';
    os << std::endl;
  }
};
