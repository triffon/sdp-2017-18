#ifndef _SET_CPP
#define _SET_CPP

#include <vector>

template <typename T, template <typename, typename> class D>
class Set {
  D<T, bool> dict;

public:
  bool empty() const {
    return dict.empty();
  }

  bool insert(T const& x) {
    return dict.add(x, false);
  }

  bool remove(T const& x) {
    return dict.remove(x);
  }

  bool contains(T const& x) {
    return dict.lookup(x) != nullptr;
  }

  std::vector<T> elements() {
    return dict.keys();
  }
};

//template <typename T>
// using BSTreeSet = Set<T, BSTreeDictionary>

#endif
