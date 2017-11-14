#ifndef __LLIST_CPP
#define __LLIST_CPP

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

  void clean() {
    T tmp;
    while(!empty())
      deleteBegin(tmp);
  }

public:

  using I = LinkedListIterator<T>;

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

  // проверка дали списък е празен
  bool empty() const {
    return front == nullptr;
  }

  // вмъкване преди позиция
  bool insertBefore(T const&, I = begin());

  // вмъкване след позиция
  bool insertAfter(T const&, I = end());

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

  // достъп до елемент на позиция
  T getAt(I) const;

  // началото на списъка
  I begin() const {
    return I(front);
  }

  // краят на списъка
  I end() const {
    return I(back);
  }

  // вмъкване в началото на списък
  void insertBegin(T const& x) {
    insertBefore(x, begin());
  }

  // вмъкване в края на списък
  void insertEnd(T const& x) {
    insertAfter(x, end());
  }

  // изтриване на първия елемент
  bool deleteBegin(T& x) {
    return deleteAt(x, begin());
  }

  // изтриване на последния елемент
  bool deleteEnd(T& x) {
    return deleteAt(x, end());
  }

};


template <typename T>
class LinkedListIterator {
private:

  using LLE = LinkedListElement<T>;
  
  LLE* ptr;

public:

  using I = LinkedListIterator<T>;

  // конструктор по указател
  LinkedListIterator(LLE* _ptr = nullptr) : ptr(_ptr) {}

  // няма нужда от голяма четворка!

  // следваща позиция
  I next() const;

  // предишна позиция
  I prev() const;

  // достъп до елемент с право на промяна
  T& get() const;

  // достъп до елемент без право на промяна
  T const& getConst() const;

  // проверка за валидност
  bool valid() const;

  // сравнение на два итератора
  bool operator==(I const& it) const {
    return ptr == it.ptr;
  }

  bool operator!=(I const& it) const {
    return !(*this == it);
  }
  
};


#endif
