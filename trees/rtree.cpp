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
  
};

template <typename T>
std::ostream& operator<<(std::ostream& os, RTree<T> const& t) {
  t.printDOT(os);
  return os;
}
