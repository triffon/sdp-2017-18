#include "UnitTestFramework.h"

// ще смятаме, че шаблонът, който тестваме е TestQueue

TEST_CASE("Queue", Queue_CreateEmptyQueue) {
  const TestQueue<int> q;
  Assert::IsTrue(q.empty());
}

TEST_CASE("Queue", Queue_EnqueueNotEmpty) {
  TestQueue<int> q;
  q.enqueue(5);
  Assert::IsTrue(!q.empty());
}

TEST_CASE("Queue", Queue_EnqueueHead) {
  TestQueue<int> q;
  for(int i = 1; i <= 100; i++)
    q.enqueue(i);
  Assert::AreEqual(q.head(), 1);
}

TEST_CASE("Queue", Queue_EnqueueDequeue) {
  TestQueue<int> q;
  for(int i = 1; i <= 100; i++)
    q.enqueue(i);
  for(int i = 1; i <= 100; i++)
    Assert::AreEqual(q.dequeue(), i);
  Assert::IsTrue(q.empty());
}
  
TEST_CASE("Queue", Queue_DequeueAfterEnqueue) {
  TestQueue<int> q;
  for(int i = 1; i <= 1000; i++) {
    q.enqueue(i);
    Assert::AreEqual(q.dequeue(), i);
  }
  Assert::IsTrue(q.empty());
}
    
TEST_CASE("Queue", Queue_NoShareAfterCopy) {
  TestQueue<int> q1;
  for(int i = 1; i <= 100; i++)
    q1.enqueue(i);
  TestQueue<int> q2 = q1;
  q1.enqueue(200);
  q1.dequeue();
  for(int i = 1; i <= 100; i++)
    Assert::AreEqual(q2.dequeue(), i);
}

TEST_CASE("Queue", Queue_NoShareAfterAssignment) {
  TestQueue<int> q1;
  for(int i = 1; i <= 100; i++)
    q1.enqueue(i);
  TestQueue<int> q2;
  q2 = q1;
  q1.enqueue(200);
  q1.dequeue();
  for(int i = 1; i <= 100; i++)
    Assert::AreEqual(q2.dequeue(), i);
}

TEST_CASE("Queue", Queue_minQueue) {
  TestQueue<int> q;
  q.enqueue(5);
  q.enqueue(6);
  q.enqueue(3);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(4);
  q.enqueue(3);
  Assert::AreEqual(minQueue(q, -1), 1);
  Assert::AreEqual(minQueue(q, -1), 2);
  Assert::AreEqual(minQueue(q, -1), 3);
  Assert::AreEqual(minQueue(q, -1), 3);
  Assert::AreEqual(minQueue(q, -1), 4);
  Assert::AreEqual(minQueue(q, -1), 5);
  Assert::AreEqual(minQueue(q, -1), 6);
}
