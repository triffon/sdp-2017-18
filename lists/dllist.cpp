#ifndef __DLLIST_CPP
#define __DLLIST_CPP

#include <iostream>

template <typename T>
struct DoubleLinkedListElement {

  DoubleLinkedListElement(T const& _data,
                          DoubleLinkedListElement* _next = nullptr,
                          DoubleLinkedListElement* _prev = nullptr) :
    data(_data), next(_next), prev(_prev) {}
  
  T data;
  DoubleLinkedListElement *next, *prev;
};

template <typename T>
class DoubleLinkedListIterator;

template <typename T>
class DoubleLinkedList {
public:

  using I = DoubleLinkedListIterator<T>;

private:

  using LLE = DoubleLinkedListElement<T>;
  
  LLE *front, *back;

  // O(n) по време, O(1) по памет
  void copy(DoubleLinkedList const& l) {
    /*
    for(I it = l.begin(); it; ++it)
      insertEnd(*it);
    */
  }

  // O(n) по време, O(1) по памет
  void clean() {
    /*
    T tmp;
    while(!empty())
      deleteBegin(tmp);
    */
  }

public:
  
  // O(1)
  // създаване на празен списък
  DoubleLinkedList() : front(nullptr), back(nullptr) {}

  // конструктор за копиране
  DoubleLinkedList(DoubleLinkedList const& l) : front(nullptr), back(nullptr) {
    copy(l);
  }

  // операция за присвояване
  DoubleLinkedList& operator=(DoubleLinkedList const& l) {
    if (this != &l) {
      clean();
      copy(l);
    }
    return *this;
  }

  // деструктор
  ~DoubleLinkedList() {
    clean();
  }

  // O(1)
  // проверка дали списък е празен
  bool empty() const {
    return front == nullptr;
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
  DoubleLinkedList& operator+=(T const& x) {
    insertEnd(x);
  }

  // O(n)
  void print(std::ostream& os = std::cout) const {
    for(I it = begin(); it; ++it)
      os << *it << ' ';
    os << std::endl;
  }

  // O(1) по време и памет
  // вмъкване преди позиция
  bool insertBefore(T const& x, I it) {
    if (it == begin()) {
      LLE* p = new LLE(x, front);
      if (empty())
        // ако списъкът е бил празен, тогава трябва back също да сочи към p
        back = p;
      else
        // а ако не е празен, трябва front->prev да сочи към новата кутия
        front->prev = p;
      front = p;
      return true;
    }

    if (!it || empty())
      return false;

    // итераторът е валиден и списъкът е непразен
    // итераторът не сочи към първия елемент
    LLE* p = new LLE(x, it.ptr, it.ptr->prev);
    it.ptr->prev = it.ptr->prev->next = p;
    return true;
    // TODO: може ли да обединим двата случая?
  }

  // O(1) по време и памет
  // вмъкване след позиция
  bool insertAfter(T const& x, I it) {
    if (it == end()) {
      LLE* p = new LLE(x, nullptr, back);
      if (empty())
        // ако списъкът е бил празен, тогава трябва front също да сочи към p
        front = p;
      else
        // а ако не е празен, трябва back->next да сочи към новата кутия
        back->next = p;
      back = p;
      return true;
    }

    if (!it || empty())
      return false;

    // итераторът е валиден и списъкът е непразен
    // итераторът не сочи към последния елемент
    LLE* p = new LLE(x, it.ptr->next, it.ptr);
    it.ptr->next = it.ptr->next->prev = p;
    return true;
    // TODO: може ли да обединим двата случая?
  }

  // изтриване на елемент на дадена позиция
  bool deleteAt(T& x, I it) {
    if (!it)
      return false;

    // итераторът е валиден
    // запомняме данната в x
    x = *it;

    if (it == begin()) {
      // частен случай: изтриваме в началото на списъка
      // прескачаме изтрития елемент
      front = front->next;
      delete it.ptr;
      if (front == nullptr)
        // списъкът остава празен, back също трябва да е nullptr
        back = nullptr;
      else
        // front е валиден, значи prev трябва да е nullptr
        front->prev = nullptr;
    } else
      if (it == end()) {
        // частен случай: изтриваме в края на списъка
        // прескачаме изтрития елемент
        back = back->prev;
        delete it.ptr;
        if (back == nullptr)
          // списъкът остава празен, front също трябва да е nullptr
          front = nullptr;
        else
          // back е валиден, значи next трябва да е nullptr
          back->next = nullptr;
      } else {
        // изтриваме вътре в списъка
        // няма да правим промени по front и back
        it.ptr->prev->next = it.ptr->next;
        it.ptr->next->prev = it.ptr->prev;
        delete it.ptr;
      }
    return true;
  }

  // изтриване на елемент преди дадена позиция
  bool deleteBefore(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.prev());
  }
  
  // изтриване на елемент след дадена позиция
  bool deleteAfter(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.next());
  }
};

// всички операции са O(1)
template <typename T>
class DoubleLinkedListIterator {
private:

  using LLE = DoubleLinkedListElement<T>;
  
  LLE* ptr;

  //  static T error;

public:

  using I = DoubleLinkedListIterator<T>;
  friend class DoubleLinkedList<T>;

  // конструктор по указател
  DoubleLinkedListIterator(LLE* _ptr = nullptr) : ptr(_ptr) {}

  // няма нужда от голяма четворка!

  // следваща позиция
  I next() const {
    // считаме, че итераторът е валиден
    // if (!valid())
    //  return *this;
    
    return I(ptr->next);
  }

  // предишна позиция
  I prev() const {
    return I(ptr->prev);
  }

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

#ifdef BLAH
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
