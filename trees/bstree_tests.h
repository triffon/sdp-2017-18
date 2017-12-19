#include "UnitTestFramework.h"
#include "bstree.cpp"

using TestBSTree = BSTree<int>;

TEST_CASE("BSTree", BSTree_CreateEmpty) {
  TestBSTree t;
  Assert::IsTrue(t.empty());
}

TEST_CASE("BSTree", BSTree_CreateSingle) {
  TestBSTree t;
  Assert::IsTrue(t.insert(5));
  // t.printDOT(std::clog);
  Assert::IsFalse(t.empty());
  Assert::IsTrue(t.search(5));
  Assert::IsFalse(t.search(7));
}

TEST_CASE("BSTree", BSTree_InsertTwice) {
  TestBSTree t;
  Assert::IsTrue(t.insert(5));
  Assert::IsFalse(t.insert(5));
}


TEST_CASE("BSTree", BSTree_CollectSorted) {
  TestBSTree t;
  t.insert(5);
  t.insert(3);
  t.insert(7);
  t.insert(4);
  t.insert(6);
  t.insert(2);
  t.insert(1);
  LinkedList<int> l;
  t.collect(l);
  int i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::AreEqual(i, 8);
}
