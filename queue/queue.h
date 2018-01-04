/*
 АТД опашка
*/

#ifndef _QUEUE_H
#define _QUEUE_H

template <typename T>
class Queue {
public:
  // проверка за празнота на опашка
  virtual bool empty() const = 0;

  // включване на елемент на края на опашката
  virtual bool enqueue(T const&) = 0;

  // изключване на елемент от началото на опашката
  virtual T dequeue() = 0;

  // достъп до първия елемент на опашката
  virtual T head() const = 0;

  // достъп до първия елемент на опашката с възможност за промяна
  virtual T& head() = 0;

  // виртуален деструктор
  virtual ~Queue() {}
};

template <typename T>
T minQueue(Queue<T>& q, T const& sentinel = T());

#endif
