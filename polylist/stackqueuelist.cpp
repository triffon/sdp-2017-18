#include "lqueue.cpp"
#include "lstack.cpp"
#include "llist.cpp"

template <typename T>
class SimpleContainer {
public:
  virtual bool add(T const&) = 0;
  virtual T remove() = 0;
  virtual bool empty() const = 0;
  virtual ~SimpleContainer() {}
};

template <typename T>
class SimpleStack : public LinkedStack<T>, public SimpleContainer<T> {
public:
  
  bool add(T const& x) {
    LinkedStack<T>::push(x);
    return true;
  }
  
  T remove() {
    return LinkedStack<T>::pop();
  }
  
  bool empty() const {
    return LinkedStack<T>::empty();
  }
  
};

template <typename T>
class SimpleQueue : public LQueue<T>, public SimpleContainer<T> {
public:
  bool add(T const& x) {
    LQueue<T>::enqueue(x);
    return true;
  }

  T remove() {
    return LQueue<T>::dequeue();
  }

  bool empty() const {
    return LQueue<T>::empty();
  }
  
};

template <typename T>
using StackQueueList = LinkedList<SimpleContainer<T>*>;
