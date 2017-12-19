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
