#ifndef _BSTREE_CPP
#define _BSTREE_CPP

#include "llist.cpp"
#include "bintree.cpp"

template <typename T>
class BSTree : public BinTree<T> {
public:
  using P = BinTreePosition<T>;

private:
  using BinTree<T>::BTN;

  P findPosition(T const& x) {
    P p = rootpos();
    while (p && *p != x)
      if (x < *p)
        // наляво
        --p;
      else
        // надясно
        ++p;
    return p;
  }

  void collectFrom(LinkedList<T>& l, P p) {
    if (p) {
      collectFrom(l, -p);
      l.insertEnd(*p);
      collectFrom(l, +p);
    }
  }

public:  

  BSTree() {}

  using BinTree<T>::empty;
  using BinTree<T>::rootpos;
  using BinTree<T>::assignFrom;

  // връща false, когато x вече е в дървото
  bool insert(T const& x) {
    P p = findPosition(x);
    // !p -- трябва да вмъкнем тук
    // *p == x -- вече го има
    if (!p) {
      assignFrom(p, BinTree<T>(x));
      return true;
    }
    return false;
  }

  bool search(T const& x) {
    return findPosition(x);
  }

  void collect(LinkedList<T>& l) {
    collectFrom(l, rootpos());
  }
};

#endif
