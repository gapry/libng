#pragma once

#include <types/function.hpp>

namespace libng {

template<class T>
LIBNG_INLINE void libng_delete(T* p) {
  delete p;
}

namespace allocator {

struct _Helper {
  template<class T>
  static constexpr T alignTo_uint(T n, T a) {
    static_assert(std::is_unsigned<T>::value, "");
    T r = n % a;
    return r ? (n + a - r) : n;
  }
};

constexpr size_t alignTo(size_t n, size_t a) {
  return _Helper::alignTo_uint(n, a);
}

} // namespace allocator

} // namespace libng