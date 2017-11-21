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
public:

  using I = LinkedListIterator<T>;

private:

  using LLE = LinkedListElement<T>;
  
  LLE *front, *back;

  // O(n) по време, O(1) по памет
  void copy(LinkedList const& l) {
    for(I it = l.begin(); it; ++it)
      insertEnd(*it);
  }

  // O(n) по време, O(1) по памет
  void clean() {
    T tmp;
    while(!empty())
      deleteBegin(tmp);
  }

  // O(n) по време, O(1) по памет
  I findPrev(I it) {
    I pit = begin();
    while (pit && pit.ptr->next != it.ptr)
      ++pit;
    return pit;
  }

public:
  
  // O(1)
  // създаване на празен списък
  LinkedList() : front(nullptr), back(nullptr) {}

  // конструктор за копиране
  LinkedList(LinkedList const& l) : front(nullptr), back(nullptr) {
    copy(l);
  }

  // операция за присвояване
  LinkedList& operator=(LinkedList const& l) {
    if (this != &l) {
      clean();
      copy(l);
    }
    return *this;
  }

  // деструктор
  ~LinkedList() {
    clean();
  }

  // O(1)
  // проверка дали списък е празен
  bool empty() const {
    return front == nullptr;
  }

  // O(n) по време, O(1) по памет
  // вмъкване преди позиция
  bool insertBefore(T const& x, I it) {
    if (it == begin()) {
      LLE* p = new LLE(x, front);
      if (empty())
        // ако списъкът е бил празен, тогава трябва back също да сочи към p
        back = p;
      front = p;
      return true;
    }

    if (!it || empty())
      return false;

    // итераторът е валиден и списъкът е непразен
    // итераторът не сочи към първия елемент
    // проверката за невалидност ще се обработи от insertAfter
    return insertAfter(x, findPrev(it));
  }

  // O(1)
  // вмъкване след позиция
  bool insertAfter(T const& x, I it) {    
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

  // изключване на елемент на позиция
  // O(n) по време и O(1) по памет
  bool deleteAt(T& x, I it) {
    if (empty() || !it)
      return false;
    // списъкът не е празен
    // итераторът е валиден
    
    if (it == begin()) {
      // изключване на елемент от началото на списъка
      // front != nullptr
      x = front->data;
      LLE* p = front;
      front = front->next;
      if (front == nullptr)
        back = nullptr;
      delete p;
      return true;
    }

    // итераторът не сочи в началото на списъка
    return deleteAfter(x, findPrev(it));
  }

  // изключване на елемент преди позиция
  // O(n) по време и O(1) по памет
  bool deleteBefore(T& x, I it) {
    if (empty() || !it || it == begin())
      return false;
    // списъкът е непразен
    // итераторът е валиден и не сочи към началото
    return deleteAt(x, findPrev(it));
  }

  // O(1)
  // изключване на елемент след позиция
  bool deleteAfter(T& x, I it) {
    if (empty() || !it || it == end())
      return false;
    // it не е в края на списъка и е валиден
    // списъкът е непразен
    LLE* p = it.ptr->next; // не може да е nullptr
    it.ptr->next = p->next; // може да е nullptr
    x = p->data;
    delete p;
    if (back == p)
      back = it.ptr;
    return true;
  }

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

  void append(LinkedList& l) {
    if (back != nullptr)
      back->next = l.front;
    else
      // първият списък е празен, насочваме front в началото
      front = l.front;

    if (l.back != nullptr)
      back = l.back;
    l.front = l.back = nullptr;
  }

  void reverse() {
    // TODO: да се реализира обръщане на място
  }

  // O(n) по време и O(1) по сложност
  int length() const {
    int n = 0;
    for(I it = begin(); it; ++it)
      ++n;
    return n;
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

// O(n) по време и O(1) по памет
template <typename T>
void append(LinkedList<T>& l1, LinkedList<T> const& l2) {
  for(LinkedListIterator<int> it = l2.begin(); it; ++it)
    l1 += *it;
}

// O(n) по време и O(1) по памет
template <typename T>
void reverse(LinkedList<T>& l) {
  LinkedListIterator<T> it = l.begin();
  T x;
  while(l.deleteAfter(x, it))
    l.insertBegin(x);
}

// O(n)
template <typename T>
void split(LinkedList<T> const& l, LinkedList<T>& l1, LinkedList<T>& l2) {

  LinkedList<T> *addNow = &l1, *addLater = &l2;
  for(LinkedListIterator<T> it = l.begin(); it; ++it) {
    addNow->insertEnd(*it);
    std::swap(addNow, addLater);
  }
}

// O(m + n)
template <typename T>
LinkedList<T> merge(LinkedList<T> const& l1, LinkedList<T> const& l2) {
  LinkedListIterator<T> it1 = l1.begin(), it2 = l2.begin();
  LinkedList<T> l;
  while (it1 && it2)
    if (*it1 < *it2)
      l += *it1++;
    else
      l += *it2++;
  // !it1 || !it2
  while (it1)
    l += *it1++;
  while (it2)
    l += *it2++;
  return l;
}

// O(n*log(n))
template <typename T>
void mergeSort(LinkedList<T>& l) {
  if (l.begin() == l.end())
    // дъно: списъкът е от 0 или 1 елемент
    return;
  // 1. разделяме списъка на две равни части
  LinkedList<T> l1, l2;
  // O(n)
  split(l, l1, l2);
  // 2. сортираме рекурсивно всяка от частите
  // O(f(n/2))
  mergeSort(l1);
  // O(f(n/2))
  mergeSort(l2);
  // O(n)
  // 3. сливаме сортираните части
  l = merge(l1, l2);
}

#endif
