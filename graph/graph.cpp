#ifndef _GRAPH_CPP
#define _GRAPH_CPP

#include <iostream>

#include "bstree_dictionary.cpp"
#include "set.cpp"
#include "lstack.cpp"

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
    for(V const& v : vertices()) {
      os << v << ";\n";
      for(I it = successors(v); it; ++it)
        os << v << " -> " << *it << ";\n";
    }
    os << "}\n";
  }
};

template <typename V>
using VI = typename Graph<V>::I;

template <typename V>
std::vector<V> noSuccessors(Graph<V>& g) {
  std::vector<V> result;
  for(V const& v : g.vertices())
    if (!g.successors(v))
      result.push_back(v);
  return result;
}

template <typename V>
std::vector<V> predecessors(Graph<V>& g, V const& v) {
  std::vector<V> result;
  for(V const& u : g.vertices())
    if (g.isEdge(u, v))
      result.push_back(u);
  return result;
}

template <typename V>
bool isSymmetric(Graph<V>& g) {
  for(V const& v : g.vertices())
    for(VI<V> it = g.successors(v); it; ++it)
      // v -> *it --> *it -> v
      if (!g.isEdge(*it, v))
        return false;
  return true;
}

template <typename V>
using Path = LinkedStack<V>;

template <typename V>
using VSet = Set<V, BSTreeDictionary>;

template <typename V>
bool hasPathDFSrec(Graph<V>& g, V const& u, V const& v, VSet<V>& visited) {
  if (u == v)
    return true;
  visited.insert(u);
  for(VI<V> it = g.successors(u); it; ++it)
    // w = *it
    if (!visited.contains(*it) && hasPathDFSrec(g, *it, v, visited))
      return true;
  return false;
}

template <typename V>
bool hasPathDFS(Graph<V>& g, V const& u, V const& v) {
  VSet<V> visited;
  return hasPathDFSrec(g, u, v, visited);
}


#endif
