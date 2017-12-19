#include "UnitTestFramework.h"
#include "heap.cpp"

using TestHeap = Heap<int>;

TEST_CASE("Heap", Heap_CreateEmpty) {
  TestHeap h;
  Assert::IsTrue(h.empty());
}

TEST_CASE("Heap", Heap_EnqueueSingle) {
  TestHeap h;
  h.enqueue(2);
  Assert::AreEqual(h.length(), 1);
  Assert::AreEqual(h.head(), 2);
}

TEST_CASE("Heap", Heap_EnqueueSingleDequeue) {
  TestHeap h;
  h.enqueue(2);
  Assert::AreEqual(h.length(), 1);
  Assert::AreEqual(h.dequeue(), 2);
  Assert::IsTrue(h.empty());  
}

TEST_CASE("Heap", Heap_EnqueueDequeue) {
  TestHeap h(20);
  int x = 1;
  for(int i = 0; i < 11; i++, (x += 3) %= 11)
    h.enqueue(x);
  // std::clog << h.length();
  Assert::AreEqual(h.length(), 11);
  //h.printDOT(std::clog, 11);
  for(x = 10; x >= 0; x--) {
    Assert::AreEqual(h.dequeue(), x);
    //h.printDOT(std::clog, x);
  }
  Assert::IsTrue(h.empty());
}

// Пирамидално сортиране (heap sort)
TEST_CASE("Heap", Heap_BuildDequeue) {
  int a[10] = { 5, 7, 2, 4, 8, 9, 6, 3, 0, 1 };
  TestHeap h(10, a);
  for(int i = 9; i >= 0; i--)
    Assert::AreEqual(h.dequeue(), i);
  Assert::IsTrue(h.empty());
  int const* b = h.toArray();
  for(int i = 0; i < 10; i++)
    Assert::AreEqual(b[i], i);
}
