#pragma once

#include <types/noncopyable.hpp>
#include <types/RefCountBase.hpp>
#include <mm/utility.hpp>

namespace libng {

template<class T>
class SPtr : public NonCopyable {
public:
  SPtr() = default;

  SPtr(T* ptr) {
    reset(ptr);
  }

  SPtr(SPtr&& rhs) {
    reset(rhs._rawptr);
    rhs._rawptr = nullptr;
  }

  ~SPtr() noexcept {
    reset(nullptr);
  }

  void operator=(T* ptr) noexcept {
    reset(ptr);
  }

  void operator=(SPtr&& rhs) {
    if (rhs._rawptr == _rawptr) {
      return;
    }
    reset(rhs._rawptr);
    rhs._rawptr = nullptr;
  }

  T* operator->() noexcept {
    return _rawptr;
  }

  operator T*() noexcept {
    return _rawptr;
  }

  T* ptr() noexcept {
    return _rawptr;
  }

  const T* ptr() const noexcept {
    return _rawptr;
  }

  void reset(T* ptr) noexcept {
    static_assert(std::is_base_of<RefCountBase, T>::value, "");

    if (ptr == _rawptr) {
      return;
    }

    if (_rawptr) {
      auto cnt = --_rawptr->_refCount;
      if (cnt <= 0) {
        libng_delete(_rawptr);
      }
    }

    _rawptr = ptr;
    if (_rawptr) {
      _rawptr->_refCount++;
    }
  }

  T* detach() {
    T* ptr  = _rawptr;
    _rawptr = nullptr;
    return ptr;
  }

private:
  T* _rawptr = nullptr;
};

} // namespace libng