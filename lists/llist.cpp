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
  using I = LinkedListIterator<T>;
  
  LLE *front, *back;

  void copy(LinkedList const&);

  void clean();

public:

  // създаване на празен списък
  LinkedList();

  // конструктор за копиране
  LinkedList(LinkedList const&);

  // операция за присвояване
  LinkedList& operator=(LinkedList const&);

  // деструктор
  ~LinkedList();

  // проверка дали списък е празен
  bool empty() const;

  // вмъкване преди позиция
  bool insertBefore(T const&, I);

  // вмъкване след позиция
  bool insertAfter(T const&, I);

  // изключване на елемент на позиция
  bool deleteAt(T&, I);

  // изключване на елемент преди позиция
  bool deleteBefore(T&, I);

  // изключване на елемент след позиция
  bool deleteAfter(T&, I);

  // достъп до елемент на позиция
  T getAt(I) const;
};

#endif
