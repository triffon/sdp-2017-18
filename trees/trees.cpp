#include <fstream>
#include "rtree_tests.h"

void RTreeDOTTest() {
  std::ofstream of("rtree.dot");
  createTestTree().printDOT(of);
}

int main() {
  RTreeDOTTest();
  RunTests();
  return 0;
}
