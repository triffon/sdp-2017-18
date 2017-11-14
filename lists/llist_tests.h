#include "UnitTestFramework.h"
#include "llist.cpp"

TEST_CASE("LinkedList", CreateEmptyList) {
  const LinkedList<int> l;
  Assert::IsTrue(l.empty());
}

TEST_CASE("LinkedList", InsertBeginNotEmptyList) {
  LinkedList<int> l;
  l.insertBegin(10);
  Assert::IsFalse(l.empty());
}

TEST_CASE("LinkedList", InsertEndNotEmptyList) {
  LinkedList<int> l;
  l.insertEnd(10);
  Assert::IsFalse(l.empty());
}

TEST_CASE("LinkedList", InsertEndTraverseList) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i++)
    // l.insertEnd(i);
    l += i;
  int i = 0;
  //  for(LinkedListIterator<int> it = l.begin(); it.valid(); it = it.next(), i++)
  // Assert::AreEqual(it.get(), i);
  for(LinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", InsertBeginTraverseList) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertBegin(i);
  int i = 9;
  for(LinkedListIterator<int> it = l.begin(); it; it++, i--)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", InsertAfterIsCorrect) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i += 2)
    l.insertEnd(i);
  for(LinkedListIterator<int> it = l.begin(); it; ++(++it)) {
    // след всяко четно вмъкваме нечетно
    l.insertAfter(*it + 1, it);
  }
  // l.print();
  int i = 0;
  for(LinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}
