#include "UnitTestFramework.h"
#include "rtree.cpp"

RTree createTestTree() {
  RTree t(1);
  return
    RTree(1)
    .addChild(RTree(2)
              .addChild(RTree(3))
              .addChild(RTree(4)
                        .addChild(RTree(5))
                        .addChild(RTree(6)))
              .addChild(RTree(7))
              .addChild(RTree(8)))
    .addChild(RTree(9))
    .addChild(RTree(10));             
}

TEST_CASE("RTree", RTree_DistanceTest) {
  RTree t = createTestTree();
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
