#include "UnitTestFramework.h"
#include "bstree_dictionary.cpp"
#include "hash.cpp"

#include <algorithm>

int testhash(int const& key) {
  return 7 * key + 1;
}

// using TestDictionary = BSTreeDictionary<int, int>;
using TestDictionary = LinkedHashTable<int, int, testhash>;

TEST_CASE("Dictionary", Dictionary_CreateEmptyKeysValues) {
  TestDictionary d;
  Assert::IsTrue(d.keys().empty());
  Assert::IsTrue(d.values().empty());  
}

TEST_CASE("Dictionary", Dictionary_LookupSinglePair) {
  TestDictionary d;
  Assert::IsTrue(d.add(2, 4));
  Assert::IsFalse(d.add(2, 4));
  Assert::AreEqual(*d.lookup(2), 4);
}

TEST_CASE("Dictionary", Dictionary_AddRemovePair) {
  TestDictionary d;
  Assert::IsFalse(d.remove(2));
  Assert::IsTrue(d.add(2, 4));
  Assert::AreEqual(*d.lookup(2), 4);
  Assert::IsTrue(d.remove(2));
  Assert::AreEqual(d.lookup(2), nullptr);
  Assert::IsFalse(d.remove(2));  
}

TestDictionary* createTestDictionary() {
  TestDictionary* d = new TestDictionary;
  for(int i = 1; i <= 10; i++)
    d->add(i, i*i);
  return d;
}

TEST_CASE("Dictionary", Dictionary_KeysAll) {
  TestDictionary* d = createTestDictionary();
  std::vector<int> keys = d->keys();
  Assert::AreEqual(keys.size(), 10);
  std::sort(keys.begin(), keys.end());
  for(int i = 1; i <= 10; i++)
    Assert::AreEqual(keys[i-1], i);
}

TEST_CASE("Dictionary", Dictionary_ValuesAll) {
  TestDictionary* d = createTestDictionary();
  std::vector<int> values = d->values();
  Assert::AreEqual(values.size(), 10);
  std::sort(values.begin(), values.end());
  for(int i = 1; i <= 10; i++)
    Assert::AreEqual(values[i-1], i * i);
}

TEST_CASE("Dictionary", Dictionary_LookupAll) {
  TestDictionary* d = createTestDictionary();
  for(int i = 10; i >= 1; i--) {
    Assert::IsTrue(d->lookup(i));
    Assert::AreEqual(*d->lookup(i), i*i);
  }
}

TEST_CASE("Dictionary", Dictionary_RemoveEven) {
  TestDictionary* d = createTestDictionary();
  for(int i = 2; i <= 10; i+=2 )
    Assert::IsTrue(d->remove(i));
  for(int i = 10; i >= 1; i--) {
    if (i % 2 == 0)
      Assert::IsFalse(d->lookup(i));
    else {
      Assert::IsTrue(d->lookup(i));
      Assert::AreEqual(*d->lookup(i), i*i);
    }
  }
}
