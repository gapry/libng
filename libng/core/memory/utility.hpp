#pragma once

#include <cstdint>

#include <types/function.hpp>

namespace libng {

template<class T>
LIBNG_INLINE void libng_delete(T* p) noexcept {
  delete p;
}

template<class Obj, class Member>
constexpr intptr_t memberOffset(Member Obj::*ptrToMember) {
  Obj* c    = nullptr;
  Member* m = &(c->*ptrToMember);
  return reinterpret_cast<intptr_t>(m);
}

namespace allocator {

struct _Helper {
  template<class T>
  static constexpr T alignTo_uint(T n, T a) {
    static_assert(std::is_unsigned<T>::value, "");
    T r = n % a;
    return r ? (n + a - r) : n; // Issue: (n + a - 1) / a * a;
  }
};

constexpr size_t alignTo(size_t n, size_t a) {
  return _Helper::alignTo_uint(n, a);
}

} // namespace allocator

} // namespace libng