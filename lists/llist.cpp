#ifndef __LLIST_CPP
#define __LLIST_CPP

#include <iostream>

template <typename T>
struct LinkedListElement {

  LinkedListElement(T const& _data, LinkedListElement* _next = nullptr) :
    data(_data), next(_next) {}
  
  T data;
  LinkedListElement* next;
};

template <typename T>
class LinkedListIterator;

template <typename T>
class LinkedList {
private:

  using LLE = LinkedListElement<T>;
  
  LLE *front, *back;

  void copy(LinkedList const&);

  // O(n) по време, O(1) по памет
  void clean() {
    T tmp;
    while(!empty())
      deleteBegin(tmp);
  }

public:

  using I = LinkedListIterator<T>;

  // O(1)
  // създаване на празен списък
  LinkedList() : front(nullptr), back(nullptr) {}

  // конструктор за копиране
  LinkedList(LinkedList const&);

  // операция за присвояване
  LinkedList& operator=(LinkedList const&);

  // деструктор
  ~LinkedList() {
    clean();
  }

  // O(1)
  // проверка дали списък е празен
  bool empty() const {
    return front == nullptr;
  }

  // вмъкване преди позиция
  bool insertBefore(T const& x, I it = begin()) {
    // засега позволяваме само включване в началото
    if (it != begin())
      return false;

    LLE* p = new LLE(x, front);
    if (empty())
      // ако списъкът е бил празен, тогава трябва back също да сочи към p
      back = p;
    front = p;

    return true;
  }

  // O(1)
  // вмъкване след позиция
  bool insertAfter(T const& x, I it = end()) {    
    if (it == end() && empty()) {
      // включване на първи елемент в празен списък
      front = back = new LLE(x);
      return true;
    } else {
      if (!it)
        return false;
      // it е валиден итератор

      // включване след произволна позиция
      // ако it == end(), тогава it.ptr == back, а it.next().ptr == nullptr
      LLE* p = new LLE(x, it.next().ptr);
      it.ptr->next = p;
      if (it == end())
        back = p;
    }
    return true;
  }

  // O(1) при изключване от началото
  // изключване на елемент на позиция
  bool deleteAt(T& x, I it) {
    // засега позволяваме само изключване от началото на списък
    if (it != begin())
      return false;

    // изключване на елемент от началото на списъка

    // не можем да изключваме от празен списък
    if (empty())
      return false;
    // списъкът не е празен
    // front != nullptr

    x = front->data;
    LLE* p = front;
    front = front->next;
    if (front == nullptr)
      back = nullptr;
    delete p;

    return true;
  }

  // изключване на елемент преди позиция
  bool deleteBefore(T&, I);

  // изключване на елемент след позиция
  bool deleteAfter(T&, I);

  // O(1)
  // достъп до елемент на позиция с възможност за промяна
  T& getAt(I it) const {
    return it.get();
  }

  // O(1)
  // началото на списъка
  I begin() const {
    return I(front);
  }

  // O(1)
  // краят на списъка
  I end() const {
    return I(back);
  }

  // вмъкване в началото на списък
  void insertBegin(T const& x) {
    insertBefore(x, begin());
  }

  // O(1)
  // вмъкване в края на списък
  void insertEnd(T const& x) {
    insertAfter(x, end());
  }

  // O(1)
  // изтриване на първия елемент
  bool deleteBegin(T& x) {
    return deleteAt(x, begin());
  }

  // изтриване на последния елемент
  bool deleteEnd(T& x) {
    return deleteAt(x, end());
  }

  // синтактична захар
  LinkedList& operator+=(T const& x) {
    insertEnd(x);
  }

  // O(n)
  void print(std::ostream& os = std::cout) const {
    for(I it = begin(); it; ++it)
      os << *it << ' ';
    os << std::endl;
  }
};

// всички операции са O(1)
template <typename T>
class LinkedListIterator {
private:

  using LLE = LinkedListElement<T>;
  
  LLE* ptr;

  //  static T error;

public:

  using I = LinkedListIterator<T>;
  friend class LinkedList<T>;

  // конструктор по указател
  LinkedListIterator(LLE* _ptr = nullptr) : ptr(_ptr) {}

  // няма нужда от голяма четворка!

  // следваща позиция
  I next() const {
    // считаме, че итераторът е валиден
    // if (!valid())
    //  return *this;
    
    return I(ptr->next);
  }

  // предишна позиция
  I prev() const;

  // достъп до елемент с право на промяна
  T& get() const {
    // допускаме, че итераторът е валиден
    // if (!valid())
    //  return error;
    return ptr->data;
  }

  // достъп до елемент без право на промяна
  T const& getConst() const;

  // проверка за валидност
  bool valid() const {
    return ptr != nullptr;
  }

  // сравнение на два итератора
  bool operator==(I const& it) const {
    return ptr == it.ptr;
  }

  bool operator!=(I const& it) const {
    return !(*this == it);
  }

  // синтактична захар

  // *it <-> it.get()
  T& operator*() const {
    return get();
  }

  // it++ <-> it = it.next(), връща старата стойност на it
  I operator++(int) {
    I prev = *this;
    ++(*this);
    return prev;
  }
  
  // ++it <-> it = it.next(), връща новата стойност на it
  I& operator++() {
    return *this = next();
  }

  // it <-> it.valid()
  operator bool() const {
    return valid();
  }
};


#endif
