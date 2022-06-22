#pragma once

#include <libng_core/libcxx/utility.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<typename T>
class unique_ptr : public libng::NonCopyable {
public:
  unique_ptr()
    : _data(nullptr) {
  }

  unique_ptr(T* const obj)
    : _data(obj) {
  }

  ~unique_ptr() noexcept {
    delete _data;
  }

  T* operator->() const {
    return _data;
  }

  T& operator*() const {
    return *_data;
  }

private:
  T* _data = nullptr;
};

template<typename T, typename... Args>
typename unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(libng::libcxx::forward<Args>(args)...));
}

} // namespace libng::libcxx

namespace libng {

template<class T>
using UPtr = eastl::unique_ptr<T>;

}
