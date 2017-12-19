#ifndef _BSTREE_CPP
#define _BSTREE_CPP

#include "llist.cpp"
#include "bintree.cpp"

template <typename T>
class BSTree : public BinTree<T> {
private:
  using BinTree<T>::BTN;
  
public:
  using P = BinTreePosition<T>;

  BSTree() {}

  using BinTree<T>::empty;
  using BinTree<T>::rootpos;
  using BinTree<T>::assignFrom;

  // връща false, когато x вече е в дървото
  bool insert(T const& x) {
    P p = rootpos();
    while (p && *p != x)
      if (x < *p)
        // наляво
        --p;
      else
        // надясно
        ++p;
    // !p -- трябва да вмъкнем тук
    // *p == x -- вече го има
    if (!p) {
      assignFrom(p, BinTree<T>(x));
      return true;
    }
    return false;
  }

  bool search(T const& x) const {
    return false;
  }

  void collect(LinkedList<T>& l) {
  }
};

#endif
