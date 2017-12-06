#include <iostream>
#include "llist.cpp"

template <typename T>
class RTree {
public:

  using I = typename LinkedList<RTree<T>>::I;

private:

  T data;
  LinkedList<RTree<T>> children;

  void print(std::ostream& os = std::cout) {
    for(I it = subtrees(); it; ++it) {
      os << root() << " -> " << (*it).root() << ";\n";
      (*it).print(os);
    }
  }

public:

  RTree(T const& _data = T()) : data(_data) {}

  T root() const { return data; }

  RTree& addChild(RTree const& t) {
    children.insertEnd(t);
    return *this;
  }

  LinkedListIterator<RTree> subtrees() const {
    return children.begin();
  }

  void printDOT(std::ostream& os = std::cout) {
    os << "digraph tree {\n";
    print(os);
    os << "}";
  }

  // разстояние на x от корена
  // връща -1, ако x не се среща в дървото
  int distance(T const& x) const {
    if (x == root())
      return 0;
    for(I it = subtrees(); it; ++it) {
      int d = (*it).distance(x);
      if (d >= 0)
        return d + 1;
    }
    return -1;
  }

  // разклоненост на дървото
  int breadth() const {
    int max = children.length();
    for(I it = subtrees(); it; ++it) {
      int b = (*it).breadth();
      if (b > max)
        max = b;
    }
    return max;
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, RTree<T> const& t) {
  t.printDOT(os);
  return os;
}
