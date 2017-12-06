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

#ifdef BLAH
TEST_CASE("RTree", RTree_DistanceTest) {
  ITree t = createTestTree();
  Assert::AreEqual(t.disance(1), 0);
  Assert::AreEqual(t.disance(2), 1);
  Assert::AreEqual(t.disance(3), 2);
  Assert::AreEqual(t.disance(4), 2);
  Assert::AreEqual(t.disance(5), 3);
  Assert::AreEqual(t.disance(6), 3);
  Assert::AreEqual(t.disance(7), 2);
  Assert::AreEqual(t.disance(8), 2);
  Assert::AreEqual(t.disance(9), 1);
  Assert::AreEqual(t.disance(10), 1);
}
#endif
