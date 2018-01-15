#include "graph.cpp"

#include <fstream>

int main() {
  Graph<int> g;
  for(int i = 1; i <= 6; i++)
    g.addVertex(i);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 3);
  g.addEdge(2, 6);
  g.addEdge(3, 4);
  g.addEdge(3, 6);
  g.addEdge(4, 1);
  g.addEdge(4, 5);
  g.addEdge(5, 3);
  g.addEdge(6, 5);
  std::ofstream fo("graph.dot");
  g.printDOT(fo);
  return 0;
}
