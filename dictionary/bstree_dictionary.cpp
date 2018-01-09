#ifndef _BSTREE_DICTIONARY
#define _BSTREE_DICTIONARY

#include "dictionary.h"
#include "bstree.cpp"

template <typename K, typename V>
class BSTreeDictionary : private BSTree<KeyValuePair<K, V>>,
                         public Dictionary<K, V> {

  using KVP = KeyValuePair<K,V>;
  using BST = BSTree<KVP>;
  using P = BinTreePosition<KVP>;

public:

  // търсене на стойност по ключ
  V* lookup(K const& key) {
    P p = BST::findPosition(key);
    if (!p)
      return nullptr;
    return &((*p).value());
  }

  // добавяне на връзка (ключ, стойност)
  virtual bool add(K const& key, V const& value) {
    return BST::insert(KVP(key, value));
  }

  // изтриване на ключ и стойността, свързана с него
  virtual bool remove(K const& key) {
    return BST::remove(key);
  }

  // списък от ключове
  virtual std::vector<K> keys() {
    LinkedList<KVP> kvps;
    BST::collect(kvps);
    std::vector<K> result;
    for(LinkedListIterator<KVP> i = kvps.begin(); i; ++i)
      result.push_back((*i).key());
    return result;
  }

  // списък от стойности
  virtual std::vector<V> values() {
    LinkedList<KVP> kvps;
    BST::collect(kvps);
    std::vector<V> result;
    for(LinkedListIterator<KVP> i = kvps.begin(); i; ++i)
      result.push_back((*i).value());
    return result;
  }
};

#endif
