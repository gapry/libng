#pragma once

#include <cassert>
#include <new>
#include <utility>
#include <fmt/core.h>

#include <types/noncopyable.hpp>
#include <exception/error.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

using size_type = int;

template<typename T>
class Vector : public NonCopyable {

public:
  Vector() = default;

  ~Vector() noexcept;

  T& operator[](int i);

  const T& operator[](int i) const;

  void resize(size_type new_size);

  void reserve(size_type n);

  size_type size(void) const;

private:
  T* m_data            = nullptr;
  size_type m_size     = 0;
  size_type m_capacity = 0;
};

template<typename T>
Vector<T>::~Vector() noexcept {
  if (m_data != nullptr) {
    std::free(m_data);
  }
}

template<typename T>
T& Vector<T>::operator[](int i) {
  return m_data[i];
}

template<typename T>
const T& Vector<T>::operator[](int i) const {
  return m_data[i];
}

template<typename T>
void Vector<T>::resize(size_type new_size) {
  if (m_size == new_size) {
    return;
  }
  reserve(new_size);
  if (new_size > m_size) {
    auto* dst = m_data + m_size;
    auto* end = m_data + new_size;
    for (; dst < end; dst++) {
      new (dst) T();
    }
  }
  m_size = new_size;
}

template<typename T>
void Vector<T>::reserve(size_type n) {
  if (m_capacity >= n) {
    return;
  }

  auto new_capacity = n;
  auto new_data     = reinterpret_cast<T*>(std::malloc(new_capacity * sizeof(T)));

  try {
    auto* src = m_data;
    auto* dst = new_data;
    auto* end = m_data + m_size;
    for (; src < end; src++, dst++) {
      new (dst) T(std::move(*src));
      src->~T();
    }
    if (m_data != nullptr) {
      std::free(m_data);
    }
  } catch (...) {
    // Issue: how to rewind
    if (new_data != nullptr) {
      std::free(new_data);
    }
    throw LIBNG_ERROR("Can't not reserve");
  }
  m_data     = new_data;
  m_capacity = new_capacity;
}

template<typename T>
size_type Vector<T>::size(void) const {
  return m_size;
}

} // namespace libng::libcxx

namespace libng {

template<class T>
using Vector = eastl::vector<T>;

}
