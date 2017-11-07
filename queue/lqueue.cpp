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
  
public:
  // конструиране на празна опашка
  LQueue() : front(nullptr), back(nullptr) {}
  
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
