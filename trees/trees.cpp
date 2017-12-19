#include <fstream>
//#include "rtree_tests.h"
#include "bintree_tests.h"
//#include "heap_tests.h"
#include "bstree_tests.h"

/*
void RTreeDOTTest() {
  std::ofstream of("rtree.dot");
  createTestTree().printDOT(of);
  }

void BinTreeDOTTest() {
  std::ofstream of("bintree.dot");
  createTestBinTree().printDOT(of);
}
*/

int main() {
  //  RTreeDOTTest();
  // BinTreeDOTTest();
  RunTests();
  return 0;
}
