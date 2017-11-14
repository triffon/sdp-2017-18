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

  void clean();

public:

  using I = LinkedListIterator<T>;

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

  // началото на списъка
  I begin() const;

  // краят на списъка
  I end() const;
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
};


#endif
