// TODO: реализирайте четене на SList от поток
// TODO: реализирайте шаблон SPrimitive<T>, който обвива произволен стандартен тип
// Примери: SPrimitive<int>, SPrimitive<double>, SPrimitive<char>, SPrimitive<std::string>
// TODO: направете конструктор за копиране и operator= за SList така че да не се споделя памет
// Упътване: Cloneable

#ifndef __SLIST_CPP
#define __SLIST_CPP

#include <iostream>
#include "llist.cpp"

class SElement {
public:

  // извеждане
  virtual void print(std::ostream& os = std::cout) const = 0;

  // събиране на числата
  virtual void collect(LinkedList<int>& l) const = 0;

  virtual ~SElement() {}
};

class SInt : public SElement {
private:
  int data;
  
public:

  SInt(int _data = 0) : data(_data) {}

  void print(std::ostream& os = std::cout) const {
    os << data;
  }

  void collect(LinkedList<int>& l) const {
    l.insertEnd(data);
  }
};

class SList : public LinkedList<SElement*>, public SElement {
public:

  using LinkedList<SElement*>::I;

  SList* add(SElement* element) {
    LinkedList<SElement*>::insertEnd(element);
    return this;
  }

  void print(std::ostream& os = std::cout) const {
    os << '(';
    I it = begin();
    while (it) {
      (*it++)->print(os);
      if (it)
        os << ' ';
    }
    os << ')';
  }

  void collect(LinkedList<int>& l) const {
    for(I it = begin(); it; ++it)
      (*it)->collect(l);
  }

  ~SList() {
    for(I it = begin(); it; ++it)
      delete *it;
  }
};

/*
template <typename T>
T* operator->(LinkedListIterator<T*>& it) {
  return it.value();
}
*/

// it->collect(l);

std::ostream& operator<<(std::ostream& os, SElement const& se) {
  se.print(os);
  return os;
}

#endif
