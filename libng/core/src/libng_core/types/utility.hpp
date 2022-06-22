#pragma once

#include <libng_core/types/function.hpp> // LIBNG_INLINE
#include <utility>                       // std::forward

#define LIBNG_FORWARD(T) (std::forward<decltype(T)>(T))

template<class T>
LIBNG_INLINE T* constCast(const T* param) {
  return const_cast<T*>(param);
}

template<class T>
LIBNG_INLINE T& constCast(const T& param) {
  return const_cast<T&>(param);
}