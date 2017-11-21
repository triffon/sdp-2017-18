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
    l += i;
  int i = 0;
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

TEST_CASE("LinkedList", InsertBeforeIsCorrect) {
  LinkedList<int> l;
  // добавяме всички четни числа
  for(int i = 2; i < 10; i += 2)
    l.insertEnd(i);
  for(LinkedListIterator<int> it = l.begin(); it; ++it) {
    // преди всяко четно вмъкваме нечетно
    l.insertBefore(*it - 1, it);
  }
  // l.print();
  int i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", DeleteAfterIsCorrect) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // изтриваме всички нечетни числа
  int i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; ++it, ++(++i)) {
    int x;
    l.deleteAfter(x, it);
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.end(), 8);
  // останали са само четните числа
  i = 0;
  for(LinkedListIterator<int> it = l.begin(); it; it++, ++(++i))
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", DeleteAtIsCorrect) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // изтриваме кратните на 3
  int i = 0;
  for(LinkedListIterator<int> it = l.begin(); it; it && ++(++it), i += 3) {
    int x;
    l.deleteAt(x, it++); // не можем да разчитаме на този итератор вече
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.begin(), 1);
  Assert::AreEqual(*l.end(), 8);
  i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; ++it, ++i) {
    // прескачаме кратните на 3
    if (i % 3 == 0)
      ++i;
    Assert::AreEqual(*it, i);
  }
}

TEST_CASE("LinkedList", DeleteBeforeIsCorrect) {
  LinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // ще изтрием четните числа
  int i = 0;
  for(LinkedListIterator<int> it = ++l.begin(); it; ++it && ++it, i += 2) {
    int x;
    l.deleteBefore(x, it);
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.begin(), 1);
  // останали са само нечетните числа
  i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; ++it, i += 2)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", LinkedList_CopyAvoidsSharing) {
  LinkedList<int>* l1 = new LinkedList<int>;
  for(int i = 0; i < 10; i++)
    l1->insertEnd(i);
  LinkedList<int> l2 = *l1;
  delete l1;
  l2.insertBegin(-1);
  l2.insertEnd(10);
  int i = -1;
  for(LinkedListIterator<int> it = l2.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", LinkedList_AssignAvoidsSharing) {
  LinkedList<int>* l1 = new LinkedList<int>;
  for(int i = 0; i < 10; i++)
    l1->insertEnd(i);
  LinkedList<int> l2;
  l2.insertBegin(100);
  l2.insertEnd(200);
  l2 = *l1;
  delete l1;
  l2.insertBegin(-1);
  l2.insertEnd(10);
  int i = -1;
  for(LinkedListIterator<int> it = l2.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", LinkedList_NonDestructiveAppendIsCorrect) {
  LinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  for(; i < 20; i++)
    l2 += i;
  append(l1, l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 19);
  i = 0;
  for(LinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("LinkedList", LinkedList_DestructiveAppendIsCorrect) {
  LinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  for(; i < 20; i++)
    l2 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 19);
  i = 0;
  for(LinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("LinkedList", LinkedList_DestructiveAppendEmptyList) {
  LinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 9);
  i = 0;
  for(LinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("LinkedList", LinkedList_EmptyListDestructiveAppend) {
  LinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l2 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 9);
  i = 0;
  for(LinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("LinkedList", LinkedList_EmptyListDestructiveAppendEmptyList) {
  LinkedList<int> l1, l2;
  l1.append(l2);
  Assert::IsTrue(l1.empty());
  Assert::IsTrue(l2.empty());  
}
