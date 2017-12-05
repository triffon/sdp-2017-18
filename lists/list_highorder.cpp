template <typename T>
using UnaryPredicate = bool (*)(T);

template <typename T>
using UnaryOperation = T (*)(T);

// typedef int (*BinaryOperation)(int,int);
template <typename T>
using BinaryOperation = T (*)(T,T);

// O(n) по време и по памет
template <typename I, typename T>
T foldr(I it, BinaryOperation<T> op, T nv) {
  /*
(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))
  (car l) <--> *it
  (cdr l) <--> ++it
  (null? l) <--> !it
  */
    if (!it)
      return nv;
  return op(*it, foldr(it.next(), op, nv));
}

// O(n) по време, O(1) по памет
template <typename I, typename T>
T foldl(I it, BinaryOperation<T> op, T nv) {
  T result = nv;
  for(;it;++it)
    result = op(result, *it);
  return result;
}

// O(n) по време и памет
template <typename L, typename T>
L map(L const& l, UnaryOperation<T> f) {
  L result;
  for(typename L::I it = l.begin(); it; ++it)
    result.insertEnd(f(*it));
  return result;
}

// O(n) по време и O(1) памет
template <typename L, typename T>
void mapd(L& l, UnaryOperation<T> f) {
  for(typename L::I it = l.begin(); it; ++it)
    *it = f(*it);
}

// O(n) по време и памет
template <typename L, typename T>
L filter(L const& l, UnaryPredicate<T> p) {
  L result;
  for(typename L::I it = l.begin(); it; ++it)
    if (p(*it))
      result.insertEnd(*it);
  return result;
}

// O(n^2) по време и O(1) памет
template <typename L, typename T>
void filterd(L& l, UnaryPredicate<T> p) {
  for(typename L::I it = l.begin(); it;)
    if (!p(*it)) {
      T tmp;
      l.deleteAt(tmp, it++);
    }
    else
      ++it;
}

// TODO: за домашно, filterd O(n) по време
