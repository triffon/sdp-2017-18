#ifndef _GRAPH_CPP
#define _GRAPH_CPP

#include <iostream>
#include <utility>

#include "bstree_dictionary.cpp"
#include "set.cpp"
#include "lstack.cpp"
#include "lqueue.cpp"

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
bool isPath(Graph<V>& g, Path<V> path) {
  if (path.empty())
    return true;
  V u = path.pop();
  while (!path.empty()) {
    V v = path.peek();
    if (!g.isEdge(v, u))
      return false;
    u = path.pop();
  }
  return true;
}

template <typename V>
void printPath(Path<V> path) {
  while (!path.empty())
    std::clog << path.pop() << ' ';
  std::clog << '\n';                              
}

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


template <typename V>
bool findPathDFSrec(Graph<V>& g, V const& u, V const& v,
                    VSet<V>& visited,
                    Path<V>& path) {
  path.push(u);
  // std::clog << "Обхождаме " << u << std::endl;
  if (u == v)
    return true;
  visited.insert(u);
  for(VI<V> it = g.successors(u); it; ++it) {
    // w = *it
    //    std::clog << "Наследник " << *it << std::endl;
    if (!visited.contains(*it) && findPathDFSrec(g, *it, v, visited, path))
      return true;
  }
  //  std::clog << "Отказваме се от " << u << std::endl;
  path.pop();
  return false;
}

template <typename V>
Path<V> findPathDFS(Graph<V>& g, V const& u, V const& v) {
  VSet<V> visited;
  Path<V> path;
  findPathDFSrec(g, u, v, visited, path);
  return path;
}

template <typename V>
bool hasPathBFS(Graph<V>& g, V const& u, V const& v) {
  VSet<V> visited;
  LQueue<V> q;
  q.enqueue(u);
  V w = u;
  while (!q.empty() && (v != (w = q.dequeue()))) {
    visited.insert(w);
    
    for(VI<V> it = g.successors(w); it; ++it)
      if (!visited.contains(*it))
        q.enqueue(*it);
  }
  // q.empty() || v == w
  return v == w;
}

template <typename V>
using Edge = std::pair<V, V>;

template <typename V>
Path<V> findPathBFS(Graph<V>& g, V const& u, V const& v) {
  VSet<V> visited;
  LQueue<V> q;
  LinkedStack<Edge<V>> edges;
  q.enqueue(u);
  visited.insert(u);
  V w = u;
  while (!q.empty() && (v != (w = q.dequeue()))) {    
    for(VI<V> it = g.successors(w); it; ++it)
      // w -> *it
      if (!visited.contains(*it)) {
        q.enqueue(*it);
        visited.insert(*it);
        edges.push({ w, *it });
        // std::clog << w << " -> " << *it << std::endl;
      }
  }
  // q.empty() || v == w
  Path<V> path;
  if (v != w)
    return path;
  // v == w
  while (!edges.empty()) {
    Edge<V> e = edges.pop();
    if (w == e.second) {
      path.push(w);
      w = e.first;
    }
  }
  path.push(u);
  // обръщаме стека
  Path<V> result;
  while (!path.empty())
    result.push(path.pop());
  return result;
}

template <typename V>
using Paths = LinkedList<Path<V>>;

template <typename V>
void allPathsDFSrec(Graph<V>& g, V const& u, V const& v,
                    VSet<V>& visited,
                    Path<V>& path,
                    Paths<V>& paths) {
  path.push(u);
  if (u == v)
    // намерихме още един път, записваме си го
    paths.insertEnd(path);
  else {
    visited.insert(u);
    for(VI<V> it = g.successors(u); it; ++it) {
      // w = *it
      if (!visited.contains(*it))
        allPathsDFSrec(g, *it, v, visited, path, paths);
    }
    // искаме да позволим повтарянето на върхове!!!
    visited.remove(u);
  }
  path.pop();
}

template <typename V>
Paths<V> allPathsDFS(Graph<V>& g, V const& u, V const& v) {
  VSet<V> visited;
  Path<V> path;
  Paths<V> paths;
  allPathsDFSrec(g, u, v, visited, path, paths);
  return paths;
}


#endif
