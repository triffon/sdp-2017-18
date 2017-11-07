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

  void copy(LQueue const& q) {
    QueueElement<T>* p = q.front;
    while (p != nullptr) {
      enqueue(p->data);
      p = p->next;
    }
  }

  void clean() {
    while (!empty())
      dequeue();
  }

  
public:
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
  
  // проверка за празнота на опашка
  bool empty() const {
    return back == nullptr;
  }

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

  // достъп до първия елемент на опашката
  T head() const {
    if (empty()) {
      std::cerr << "Опит за достъп до началото на празна опашка!\n";
      return error;
    }

    return front->data;
  }

  // достъп до първия елемент на опашката с възможност за промяна
  T& head() {
    if (empty()) {
      std::cerr << "Опит за достъп до началото на празна опашка!\n";
      return error;
    }

    return front->data;
  }
    
};
