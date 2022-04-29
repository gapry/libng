#pragma once

#include <types/function.hpp>

template<class T>
LIBNG_INLINE void libng_delete(T* p) {
  delete p;
}