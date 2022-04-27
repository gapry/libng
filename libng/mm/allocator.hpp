#pragma once

#include "pch.hpp"

namespace libng {

template<class T>
class allocator {
public:
  using value_type = T;
  using size_type  = std::size_t;

  struct rebind {
    using other = allocator<T>;
  };

  allocator() throw() = default;

  allocator(const allocator&) throw() = default;

  ~allocator() throw() = default;

  T* allocate(size_t num_of_object) {
    return static_cast<T*>(operator new(sizeof(T) * num_of_object));
  }

  void deallocate(T* ptr, size_t size) noexcept {
    operator delete(ptr);
  }

  void construct(T* ptr) {
    new ((void*)ptr) T();
  }

  void construct(T* ptr, const T& value) {
    new ((void*)ptr) T(value);
  }

  template<class... Args>
  void construct(T* ptr, Args&&... args) {
    new (ptr) T(std::forward<Args>(args)...);
  }

  void destory(T* ptr) noexcept {
    ptr->~T();
  }
};

} // namespace libng
