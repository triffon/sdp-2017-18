#ifndef _HEAP_CPP
#define _HEAP_CPP

#include <iostream>

template <typename T>
class Heap {
  
private:
  T* a;
  int size, capacity;

  // TODO: голяма четворка

  bool full() const {
    return size == capacity;
  }

  int parent(int pos) const {
    return (pos - 1) / 2;
  }

  void siftUp(int pos) {
    while (pos > 0 && a[pos] > a[parent(pos)]) {
      std::swap(a[pos], a[parent(pos)]);
      pos = parent(pos);
    }
  }

  int left(int pos) const {
    return 2 * pos + 1;
  }

  int right(int pos)  const {
    return 2 * pos + 2;
  }

  int maxChild(int pos) const {
    if (left(pos) == size - 1 || // лявото дете е последното листо в пирамидата
        a[left(pos)] > a[right(pos)])
      return left(pos);
    return right(pos);
  }

  bool isLeaf(int pos) const {
    return left(pos) >= size;
  }

  void siftDown(int pos) {
    int m;
    while (!isLeaf(pos) && a[pos] < a[m = maxChild(pos)]) {
      //      std::clog << "Разменяме " << a[pos] << " с " << a[m] << "\n";
      std::swap(a[pos], a[m]);
      pos = m;
    } 
  }
  
public:
  Heap(int _n = 10, T* _a = nullptr) : size(0), capacity(_n) {
    a = new T[capacity];
    if (_a != nullptr)
      for(int i = 0; i < capacity; i++)
        enqueue(_a[i]);
  }

  ~Heap() {
    delete[] a;
  }

  int length() const {
    return size;
  }

  bool empty() const {
    return size == 0;
  }

  bool enqueue(T const& x) {
    if (full())
      return false;

    a[size++] = x;
    
    siftUp(size - 1);
    
    return true;
  }

  T head () const {
    return a[0];
  }

  T dequeue() {
    if (empty())
      return T();

    std::swap(a[0], a[--size]);
    siftDown(0);
    return a[size];
  }

  void printDOT(std::ostream& os = std::cout, int index = 0) const {
    os << "digraph heap" << index << " {\n";
    for(int pos = 0; !isLeaf(pos); pos++) {
      os << a[pos] << " -> " << a[left(pos)] << std::endl;
      if (right(pos) < size)
        os << a[pos] << " -> " << a[right(pos)] << std::endl;
    }
    os << "}\n";
  }
};

#endif
