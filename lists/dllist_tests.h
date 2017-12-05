#include "UnitTestFramework.h"
#include "dllist.cpp"
#include "list_highorder.cpp"
#include <cmath>

TEST_CASE("DoubleLinkedList", DoubleLinkedList_CreateEmptyList) {
  const DoubleLinkedList<int> l;
  Assert::IsTrue(l.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertBeginNotEmptyList) {
  DoubleLinkedList<int> l;
  l.insertBegin(10);
  Assert::IsFalse(l.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertEndNotEmptyList) {
  DoubleLinkedList<int> l;
  l.insertEnd(10);
  Assert::IsFalse(l.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertEndTraverseList) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertBeginTraverseList) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertBegin(i);
  int i = 9;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it++, i--)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertAfterIsCorrect) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i += 2)
    l.insertEnd(i);
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++(++it)) {
    // след всяко четно вмъкваме нечетно
    l.insertAfter(*it + 1, it);
  }
  // l.print();
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_InsertBeforeIsCorrect) {
  DoubleLinkedList<int> l;
  // добавяме всички четни числа
  for(int i = 2; i < 10; i += 2)
    l.insertEnd(i);
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it) {
    // преди всяко четно вмъкваме нечетно
    l.insertBefore(*it - 1, it);
  }
  // l.print();
  int i = 1;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it++, i++)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_DeleteAfterIsCorrect) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // изтриваме всички нечетни числа
  int i = 1;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, ++(++i)) {
    int x;
    l.deleteAfter(x, it);
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.end(), 8);
  // останали са само четните числа
  i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it++, ++(++i))
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_DeleteAtIsCorrect) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // изтриваме кратните на 3
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; it && ++(++it), i += 3) {
    int x;
    l.deleteAt(x, it++); // не можем да разчитаме на този итератор вече
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.begin(), 1);
  Assert::AreEqual(*l.end(), 8);
  i = 1;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, ++i) {
    // прескачаме кратните на 3
    if (i % 3 == 0)
      ++i;
    Assert::AreEqual(*it, i);
  }
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_DeleteBeforeIsCorrect) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l += i;
  // ще изтрием четните числа
  int i = 0;
  for(DoubleLinkedListIterator<int> it = ++l.begin(); it; ++it && ++it, i += 2) {
    int x;
    l.deleteBefore(x, it);
    Assert::AreEqual(x, i);
  }
  Assert::AreEqual(*l.begin(), 1);
  // останали са само нечетните числа
  i = 1;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, i += 2)
    Assert::AreEqual(*it, i);
}

#ifdef BLAH

TEST_CASE("DoubleLinkedList", DoubleLinkedList_CopyAvoidsSharing) {
  DoubleLinkedList<int>* l1 = new DoubleLinkedList<int>;
  for(int i = 0; i < 10; i++)
    l1->insertEnd(i);
  DoubleLinkedList<int> l2 = *l1;
  delete l1;
  l2.insertBegin(-1);
  l2.insertEnd(10);
  int i = -1;
  for(DoubleLinkedListIterator<int> it = l2.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_AssignAvoidsSharing) {
  DoubleLinkedList<int>* l1 = new DoubleLinkedList<int>;
  for(int i = 0; i < 10; i++)
    l1->insertEnd(i);
  DoubleLinkedList<int> l2;
  l2.insertBegin(100);
  l2.insertEnd(200);
  l2 = *l1;
  delete l1;
  l2.insertBegin(-1);
  l2.insertEnd(10);
  int i = -1;
  for(DoubleLinkedListIterator<int> it = l2.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_NonDestructiveAppendIsCorrect) {
  DoubleLinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  for(; i < 20; i++)
    l2 += i;
  append(l1, l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 19);
  i = 0;
  for(DoubleLinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_DestructiveAppendIsCorrect) {
  DoubleLinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  for(; i < 20; i++)
    l2 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 19);
  i = 0;
  for(DoubleLinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_DestructiveAppendEmptyList) {
  DoubleLinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l1 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 9);
  i = 0;
  for(DoubleLinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_EmptyListDestructiveAppend) {
  DoubleLinkedList<int> l1, l2;
  int i;
  for(i = 0; i < 10; i++)
    l2 += i;
  l1.append(l2);
  Assert::AreEqual(*l1.begin(), 0);
  Assert::AreEqual(*l1.end(), 9);
  i = 0;
  for(DoubleLinkedListIterator<int> it = l1.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::IsTrue(l2.empty());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_EmptyListDestructiveAppendEmptyList) {
  DoubleLinkedList<int> l1, l2;
  l1.append(l2);
  Assert::IsTrue(l1.empty());
  Assert::IsTrue(l2.empty());  
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_ReverseIsCorrect) {
  DoubleLinkedList<int> l;
  int i;
  for(i = 0; i < 10; i++)
    l += i;
  reverse(l);
  i = 9;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, --i)
    Assert::AreEqual(*it, i);
}
  
TEST_CASE("DoubleLinkedList", DoubleLinkedList_ReverseInPlaceIsCorrect) {
  DoubleLinkedList<int> l;
  int i;
  for(i = 0; i < 10; i++)
    l += i;
  l.reverse();
  i = 9;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, --i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_LengthIsCorrect) {
  DoubleLinkedList<int> l;
  Assert::AreEqual(l.length(), 0);
  for(int i = 0; i < 10; i++)
    l += i;
  Assert::AreEqual(l.length(), 10);
}


TEST_CASE("DoubleLinkedList", DoubleLinkedList_SplitEvenLength) {
  DoubleLinkedList<int> l, l1, l2;
  for(int i = 0; i < 10; i++)
    l += i;
  split(l, l1, l2);
  Assert::AreEqual(l1.length(), l2.length());
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_SplitOddLength) {
  DoubleLinkedList<int> l, l1, l2;
  for(int i = 0; i < 9; i++)
    l += i;
  split(l, l1, l2);
  Assert::IsTrue(std::abs(l1.length() - l2.length()) == 1);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_MergeSorted) {
  DoubleLinkedList<int> l1, l2;
  for(int i = 0; i < 10; i++) {
    l1 += 2*i;
    l2 += 2*i + 1;
  }
  DoubleLinkedList<int> l = merge(l1, l2);
  int i = 0;
  Assert::AreEqual(*l.begin(), 0);
  Assert::AreEqual(*l.end(), 19);
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_MergeSortSorts) {
  DoubleLinkedList<int> l;
  int x = 5;
  for(int i = 0; i < 11; i++) {
    l += x;
    // 5 -> 2 -> 3 -> 10 -> 4 -> ...
    (x += 7) %= 11;
  }
  // l.print();
  mergeSort(l);
  Assert::AreEqual(*l.begin(), 0);
  Assert::AreEqual(*l.end(), 10);  
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
}

int myplus(int x, int y) {
  return x + y;
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_SumWithFoldr) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  Assert::AreEqual(foldr(l.begin(), myplus, 0), 45);
}

std::string myappend(std::string s1, std::string s2) {
  return s1 + " " + s2;
}

// myappend(s1, myappend(s2, s3))
// myappend(myappend(s1, s2), s3)

TEST_CASE("DoubleLinkedList", DoubleLinkedList_AppendWithFoldr) {
  DoubleLinkedList<std::string> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(std::to_string(i));
  Assert::AreEqual(foldr(l.begin(), myappend, std::to_string(10)), "0 1 2 3 4 5 6 7 8 9 10");
}


TEST_CASE("DoubleLinkedList", DoubleLinkedList_SumWithFoldl) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  Assert::AreEqual(foldl(l.begin(), myplus, 0), 45);
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_AppendWithFoldl) {
  DoubleLinkedList<std::string> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(std::to_string(i));
  Assert::AreEqual(foldl(l.begin(), myappend, std::to_string(10)), "10 0 1 2 3 4 5 6 7 8 9");
}

int square(int x) {
  return x * x;
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_SquareWithMap) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  DoubleLinkedList<int> l2 = map(l, square);
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l2.begin(); it; ++it, ++i)
    Assert::AreEqual(i*i, *it);
}


TEST_CASE("DoubleLinkedList", DoubleLinkedList_SquareWithMapD) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  mapd(l, square);
  int i = 0;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, ++i)
    Assert::AreEqual(i*i, *it);
}

bool isodd(int x) {
  return x % 2 != 0;
}

TEST_CASE("DoubleLinkedList", DoubleLinkedList_OddsWithFilter) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  DoubleLinkedList<int> l2 = filter(l, isodd);
  int i = 1;
  for(DoubleLinkedListIterator<int> it = l2.begin(); it; ++it, i += 2)
    Assert::AreEqual(i, *it);
}


TEST_CASE("DoubleLinkedList", DoubleLinkedList_OddsWithFilterD) {
  DoubleLinkedList<int> l;
  for(int i = 0; i < 10; i++)
    l.insertEnd(i);
  filterd(l, isodd);
  int i = 1;
  for(DoubleLinkedListIterator<int> it = l.begin(); it; ++it, i += 2)
    Assert::AreEqual(i, *it);
}


// T* operator+(T* x) { return x; }

TEST_CASE("DoubleLinkedList", DoubleLinkedList_SumOddSquares) {
  DoubleLinkedList<int> l;
  for(int i = 1; i <= 5; i++)
    l.insertEnd(i);
  Assert::AreEqual(
                   foldl(
                         filter(
                                map(l, +[](int x) { return x * x; }),
                                +[](int x) { return x % 2 != 0; })
                         .begin(),
                         +[](int x, int y) { return x + y; }, 0),
                   35);
}

// TODO: SumOddSquaresD
#endif
