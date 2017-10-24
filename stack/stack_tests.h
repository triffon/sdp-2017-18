#include "UnitTestFramework.h"

TEST_CASE("LinkedStack", LinkedStack_CreateEmpty) {
  const LinkedStack<int> s;
  Assert::IsTrue(s.empty());
}

TEST_CASE("LinkedStack", LinkedStack_PushNotEmpty) {
  LinkedStack<int> s;
  s.push(10);
  Assert::IsFalse(s.empty());
}

TEST_CASE("LinkedStack", LinkedStack_PushPeek) {
  LinkedStack<int> s;
  s.push(10);
  Assert::AreEqual(s.peek(), 10);
}

TEST_CASE("LinkedStack", LinkedStack_PushPop) {
  LinkedStack<int> s;
  int i;
  for(i = 0; i < 10; i++)
    s.push(i);
  s.push(20);
  s.pop();
  // i == 10
  for(i--; i >=0; i--)
    Assert::AreEqual(s.pop(), i);
  Assert::IsTrue(s.empty());
}
