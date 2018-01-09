#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <vector>

template <typename K, typename V>
class Dictionary {
public:

  // d[k] = v;
  // std::cout << d[k];
  V& operator[](K const& key) {
    V* pv = lookup(key);
    if (pv)
      // ако вече има стойност, връщаме неин псевдоним
      return *pv;
    // иначе, правим си нова асоциация със стойност по подразбиране
    add(key, V());
    // и я връщаме
    return *lookup(key);
  }

  // търсене на стойност по ключ
  virtual V* lookup(K const&) = 0;

  // добавяне на връзка (ключ, стойност)
  virtual bool add(K const&, V const&) = 0;

  // изтриване на ключ и стойността, свързана с него
  virtual bool remove(K const&) = 0;

  // списък от ключове
  virtual std::vector<K> keys() = 0;

  // списък от стойности
  virtual std::vector<V> values() = 0;

  virtual ~Dictionary() {}
};

#endif
