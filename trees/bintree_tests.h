#include "UnitTestFramework.h"
#include "bintree.cpp"

using BITree = BinTree<int>;

BITree createTestBinTree() {
  BITree t(1,
           BITree(2, 3, 4),
           BITree(5, 6));
  return t;
}

BITree* createTestBinTreeOnHeap() {
  BITree* t = new BITree
    (1,
     BITree(2, 3, 4),
     BITree(5, 6));
  return t;
}


TEST_CASE("BinTree", BinTree_CreateEmpty) {
  BITree t;
  Assert::IsTrue(t.empty());
}

TEST_CASE("BinTree", BinTree_TestBinTreeNotEmpty) {
  Assert::IsFalse(createTestBinTree().empty());
}

TEST_CASE("BinTree", BinTree_Root) {
  Assert::AreEqual(createTestBinTree().root(), 1);
}

TEST_CASE("BinTree", BinTree_CountNodesEmpty) {
  Assert::AreEqual(BITree().count(), 0);
}

TEST_CASE("BinTree", BinTree_CountNodesTestTree) {
  Assert::AreEqual(createTestBinTree().count(), 6);
}

TEST_CASE("BinTree", BinTree_CountNodesTestTreeOnHeap) {
  BITree* t = createTestBinTreeOnHeap();
  Assert::AreEqual(t->count(), 6);
}

TEST_CASE("BinTree", BinTree_CountNodeNewDelete) {
  BITree* t1 = createTestBinTreeOnHeap();  
  BITree* t2 = createTestBinTreeOnHeap();
  BITree* t = new BITree(0, *t1, *t2);
  delete t1;
  delete t2;
  Assert::AreEqual(t->count(), 13);
  delete t;
}

