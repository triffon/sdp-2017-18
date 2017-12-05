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
    for(I it = l.begin(); it; ++it)
      insertEnd(*it);
  }

  // O(n) по време, O(1) по памет
  void clean() {
    T tmp;
    while(!empty())
      deleteBegin(tmp);
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

  // O(1) по време и по памет
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

  // O(1) по време и по памет
  // изтриване на елемент преди дадена позиция
  bool deleteBefore(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.prev());
  }

  // O(1) по време и по памет
  // изтриване на елемент след дадена позиция
  bool deleteAfter(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.next());
  }

  void append(DoubleLinkedList& l) {
    if (back != nullptr)
      back->next = l.front;
    else
      // първият списък е празен, насочваме front в началото
      front = l.front;

    if (l.back != nullptr) {
      back = l.back;
      l.front->prev = back;
    }
    l.front = l.back = nullptr;
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

  // it-- <-> it = it.prev(), връща старата стойност на it
  I operator--(int) {
    I prev = *this;
    --(*this);
    return prev;
  }
  
  // --it <-> it = it.prev(), връща новата стойност на it
  I& operator--() {
    return *this = prev();
  }
 
  // it <-> it.valid()
  operator bool() const {
    return valid();
  }
};

// O(n) по време и O(1) по памет
template <typename T>
void append(DoubleLinkedList<T>& l1, DoubleLinkedList<T> const& l2) {
  for(DoubleLinkedListIterator<int> it = l2.begin(); it; ++it)
    l1 += *it;
}

// O(n) по време и O(1) по памет
template <typename T>
void reverse(DoubleLinkedList<T>& l) {
  for(DoubleLinkedListIterator<int> nit = l.begin(), pit = l.end();
      nit != pit && nit && nit.prev() != pit;
      ++nit, --pit)
    std::swap(*nit, *pit);
}

template <typename T>
bool isPalindrome(DoubleLinkedList<T>& l) {
  DoubleLinkedListIterator<int> nit = l.begin(), pit = l.end();
  while (nit && nit != pit && nit.prev() != pit && *nit == *pit) {
    ++nit;
    --pit;
  }
  // лошият случай: *nit != *pit
  // добрият случай: !nit || nit == pit || nit.prev() == pit
  return !nit || *nit == *pit;
}


#endif
