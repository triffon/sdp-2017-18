#include <sstream>

#include "UnitTestFramework.h"
#include "bintree.cpp"

using BITree = BinTree<int>;
using BIPos = BinTreePosition<int>;
using BCTree = BinTree<char>;
using BCPos = BinTreePosition<char>;

BITree createTestBinTree() {
  return BITree(1,
                BITree(2, 3, 4),
                BITree(5, 6));
}

BITree* createTestBinTreeOnHeap() {
  return new BITree
    (1,
     BITree(2, 3, 4),
     BITree(5, 6));
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

TEST_CASE("BinTree", BinTree_TestPosition) {
  BITree t = createTestBinTree();
  BIPos p = t;
  /*
  Assert::AreEqual(*p, 1);
  Assert::AreEqual(*p.left(), 2);
  Assert::AreEqual(*p.right(), 5);
  Assert::AreEqual(*p.left().left(), 3);
  Assert::AreEqual(*p.left().right(), 4);
  Assert::AreEqual(*p.right().left(), 6);
  */
  Assert::AreEqual(*p, 1);
  Assert::AreEqual(*-p, 2);
  Assert::AreEqual(*+p, 5);
  Assert::AreEqual(*-(-p), 3);
  Assert::AreEqual(*+-p, 4);
  Assert::AreEqual(*-+p, 6);
}

TEST_CASE("BinTree", BinTree_DepthEmpty) {
  Assert::AreEqual(depth(BIPos(BITree())), 0);
}

TEST_CASE("BinTree", BinTree_DepthTestTree) {
  Assert::AreEqual(depth(BIPos(createTestBinTree())), 3);
}

TEST_CASE("BinTree", BinTree_Equal) {
  Assert::IsTrue(createTestBinTree() == createTestBinTree());
}

TEST_CASE("BinTree", BinTree_NotEqual) {
  Assert::IsFalse(createTestBinTree() == BITree());
}

TEST_CASE("BinTree", BinTree_TestExpressionDigit) {
  std::istringstream expr("2");
  BCTree t = createExpressionTree(expr);
  BCPos p = t;
  Assert::AreEqual(*p, '2');
  Assert::IsTrue(!-p && !+p);
}

TEST_CASE("BinTree", BinTree_TestSimpleExpression) {
  std::istringstream expr("(3+4)");
  BCTree t = createExpressionTree(expr);
  BCPos p = t;
  Assert::AreEqual(*p, '+');
  Assert::AreEqual(*-p, '3');
  Assert::AreEqual(*+p, '4');
}

TEST_CASE("BinTre", BinTree_CalculateExpressionDigit) {
  std::istringstream expr("2");
  Assert::AreEqual(calculateExpressionTree(createExpressionTree(expr).rootpos()), 2);
}

TEST_CASE("BinTre", BinTree_CalculateSimpleExpression) {
  std::istringstream expr("(3+4)");
  Assert::AreEqual(calculateExpressionTree(createExpressionTree(expr).rootpos()), 7);
}

TEST_CASE("BinTre", BinTree_CalculateComplexExpression) {
  std::istringstream expr("((3+4)*(2-5))");
  Assert::AreEqual(calculateExpressionTree(createExpressionTree(expr).rootpos()), -21);
}
