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

  // O(h)
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

  // O(n)
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
  // O(h)
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

  // O(h)
  bool search(T const& x) {
    return findPosition(x);
  }

  // O(n)
  void collect(LinkedList<T>& l) {
    collectFrom(l, rootpos());
  }

  // O(h)
  bool remove(T const& x) {
    P p = findPosition(x);
    if (!p)
      return false;
    if (-p && +p) {
      // търсим минималния елемент в дясното поддърво
      P m = +p;
      // вървим наляво докато можем, т.е. докато -m е валидна позиция
      while (-m) --m;
      // !(-m)
      // записваме стойността на m на мястото на корена
      // TODO: вместо това, разменете тройните кутии на корена (p) и m
      *p = *m;
      // сега трябва да изтрием m
      // но това вече знаем как се прави! (виж долу)
      p = m;
    }
    // !-p || !+p
    P newP = -p ? -p : +p;
    // закачаме непразното поддърво за p, изтривайки стария възел
    assignFrom(p, newP);
    return true;
  }
};

#endif
