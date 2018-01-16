#ifndef _HASH_CPP
#define _HASH_CPP

#include "dictionary.h"

template <typename K>
using HashFunction = int (*)(K const&);

template <typename K>
int defaultHashFunction(K const& key) {
  // просто конвертираме в int, както можем
  return key;
}

template <typename K, typename V, HashFunction<K> hf = defaultHashFunction>
class LinkedHashTable : public Dictionary<K, V> {
  // масив с фиксирана дължина от "кофи"
  // "кофата" е списък от двойки KeyValuePair

  using KVP = KeyValuePair<K, V>;
  using Bucket = LinkedList<KVP>;
  using I = typename Bucket::I;
  
  Bucket* table;

  int capacity, size;
  static const int DEFAULT_CAPACITY = 101;

  Bucket& findBucket(K const& key) {
    return table[hf(key) % capacity];
  }
  
  I findPosition(K const& key) {
    return findBucket(key).begin();
  }

public:
  LinkedHashTable(int _capacity = DEFAULT_CAPACITY) :
    capacity(_capacity), size(0) {
    table = new Bucket[capacity];
  }
  
  // търсене на стойност по ключ
  V* lookup(K const& key) {
    for(I it = findPosition(key); it; ++it)
      if ((*it).key() == key)
        return &(*it).value();
    return nullptr;
  }

  // добавяне на връзка (ключ, стойност)
  bool add(K const& key, V const& value) {
    Bucket& b = findBucket(key);
    for(I it = b.begin(); it; ++it)
      if ((*it).key() == key)
        return false;
    b.insertEnd({key, value});
    ++size;
    return true;
  }

  // изтриване на ключ и стойността, свързана с него
  bool remove(K const& key) {
    Bucket& b = findBucket(key);
    KVP tmp;
    for(I it = b.begin(); it; ++it)
      if ((*it).key() == key) {
        --size;
        return b.deleteAt(tmp, it);
      }
    return false;
  }

  // списък от ключове
  std::vector<K> keys() {
    std::vector<K> result;
    for(int i = 0; i < capacity; ++i)
      for(I it = table[i].begin(); it; ++it)
        result.push_back((*it).key());
    return result;
  }

  // списък от стойности
  std::vector<V> values() {
    std::vector<V> result;
    for(int i = 0; i < capacity; ++i)
      for(I it = table[i].begin(); it; ++it)
        result.push_back((*it).value());
    return result;
  }


  // проверка за празнота
  bool empty() {
    return size == 0;
  }

  ~LinkedHashTable() {
    delete[] table;
  }
};

#endif
