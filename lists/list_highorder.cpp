template <typename T>
using UnaryPredicate = bool (*)(T);

template <typename T>
using UnaryOperation = T (*)(T);

// typedef int (*BinaryOperation)(int,int);
template <typename T>
using BinaryOperation = T (*)(T,T);

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
  I sit = it++;
  return op(*sit, foldr(it, op, nv));
}

template <typename I, typename T>
T foldl(I it, BinaryOperation<T> op, T nv) {
  T result = nv;
  for(;it;++it)
    result = op(result, *it);
  return result;
}

template <typename L, typename T>
L map(L const& l, UnaryOperation<T> f) {
  L result;
  for(typename L::I it = l.begin(); it; ++it)
    result.insertEnd(f(*it));
  return result;
}

template <typename L, typename T>
void mapd(L& l, UnaryOperation<T> f) {
  for(typename L::I it = l.begin(); it; ++it)
    *it = f(*it);
}

template <typename L, typename T>
L filter(L const& l, UnaryPredicate<T> p) {
  L result;
  for(typename L::I it = l.begin(); it; ++it)
    if (p(*it))
      result.insertEnd(*it);
  return result;
}


template <typename L, typename T>
void filterd(L& l, UnaryPredicate<T> p) {
  for(typename L::I it = l.begin(); it; ++it)
    if (p(*it))
      (*it);
}
