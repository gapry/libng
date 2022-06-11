#pragma once

#include <utility>                       // std::forward
#include <libng_core/types/function.hpp> // LIBNG_INLINE

#define LIBNG_FORWARD(T) (std::forward<decltype(T)>(T))

template<class T>
LIBNG_INLINE T* constCast(const T* param) {
  return const_cast<T*>(param);
}

template<class T>
LIBNG_INLINE T& constCast(const T& param) {
  return const_cast<T&>(param);
}