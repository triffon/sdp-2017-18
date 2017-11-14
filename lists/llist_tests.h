#include "UnitTestFramework.h"
#include "llist.cpp"

TEST_CASE("LinkedList", CreateEmptyList) {
  const LinkedList<int> l;
  Assert::IsTrue(l.empty());
}
