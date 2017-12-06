#include "UnitTestFramework.h"
#include "rtree.cpp"

using ITree = RTree<int>;

ITree createTestTree() {
  ITree t(1);
  return
    ITree(1)
    .addChild(ITree(2)
              .addChild(ITree(3))
              .addChild(ITree(4)
                        .addChild(ITree(5))
                        .addChild(ITree(6)))
              .addChild(ITree(7))
              .addChild(ITree(8)))
    .addChild(ITree(9))
    .addChild(ITree(10));             
}

TEST_CASE("RTree", RTree_DistanceTest) {
  ITree t = createTestTree();
  Assert::AreEqual(t.distance(1), 0);
  Assert::AreEqual(t.distance(2), 1);
  Assert::AreEqual(t.distance(3), 2);
  Assert::AreEqual(t.distance(4), 2);
  Assert::AreEqual(t.distance(5), 3);
  Assert::AreEqual(t.distance(6), 3);
  Assert::AreEqual(t.distance(7), 2);
  Assert::AreEqual(t.distance(8), 2);
  Assert::AreEqual(t.distance(9), 1);
  Assert::AreEqual(t.distance(10), 1);
}

TEST_CASE("RTree", RTree_BreadthTest) {
  Assert::AreEqual(createTestTree().breadth(), 4);
}
