#include "UnitTestFramework.h"
#include "stackqueuelist.cpp"

TEST_CASE("StackQueueList", StackQueueList_RemoveTest) {
  SimpleQueue<int> q;
  SimpleStack<int> s;
  for(int i = 0; i < 10; i++)
    q.enqueue(i);
  for(int i = 9; i >= 0; i--)
    s.push(i);
  StackQueueList<int> l;
  l.insertEnd(&q);
  l.insertEnd(&s);
  for(int i = 0; i < 10; i++)
    for(StackQueueList<int>::I it = l.begin(); it; ++it)
      Assert::AreEqual((*it)->remove(), i);
  for(StackQueueList<int>::I it = l.begin(); it; ++it)
    Assert::IsTrue((*it)->empty());
}

TEST_CASE("StackQueueList", StackQueueList_AddTest) {
  SimpleQueue<int> q;
  SimpleStack<int> s;
  StackQueueList<int> l;
  l.insertEnd(&q);
  l.insertEnd(&s);
  for(int i = 0; i < 10; i++)
    for(StackQueueList<int>::I it = l.begin(); it; ++it)
      (*it)->add(i);
  for(int i = 0; i < 10; i++)
    Assert::AreEqual(q.dequeue(), i);
  Assert::IsTrue(q.empty());
  for(int i = 9; i >= 0; i--)
    Assert::AreEqual(s.pop(), i);
  Assert::IsTrue(s.empty());
}
