#ifndef _GRAPH_CPP
#define _GRAPH_CPP

#include <iostream>

#include "bstree_dictionary.cpp"

template <typename V>
class Graph {
private:
  BSTreeDictionary<V, LinkedList<V>> g;

public:

  using I = LinkedListIterator<V>;

  std::vector<V> vertices() {
    return g.keys();
  }

  I successors(V const& v) {
    LinkedList<V>* s = g.lookup(v);
    if (s == nullptr)
      return I();
    return s->begin();
  }

  bool isEdge(V const& u, V const& v) {
    return member(successors(u), v);
  }

  bool addVertex(V const& u) {
    return g.add(u, LinkedList<V>());
  }

  bool addEdge(V const& u, V const& v) {
    if (isEdge(u, v))
      return false;
    g[u].insertEnd(v);
    return true;
  }

  bool printDOT(std::ostream& os = std::cout) {
    os << "digraph g {\n";
    for(V v : vertices()) {
      os << v << ";\n";
      for(I it = successors(v); it; ++it)
        os << v << " -> " << *it << ";\n";
    }
    os << "}\n";
  }
};

#endif