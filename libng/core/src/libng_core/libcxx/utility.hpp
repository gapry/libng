#pragma once

#include <functional>
#include <utility>

namespace libng::libcxx {

template<class T>
struct remove_reference {
  using type                = T;
  using data_read_only_type = const T;
};

template<class T>
using remove_reference_type = typename remove_reference<T>::type;

template<class T>
using remove_reference_const_type = typename remove_reference<T>::data_read_only_type;

template<class T>
T&& forward(libng::libcxx::remove_reference_type<T>& arg) noexcept {
  return static_cast<T&&>(arg);
}

template<class T>
T&& forward(libng::libcxx::remove_reference_const_type<T>& arg) noexcept {
  return static_cast<T&&>(arg);
}

} // namespace libng::libcxx

namespace libng {

// Issue: libng/core/types/utility.hpp
template<class T>
std::function<T && (typename std::remove_reference_t<T>::type&)>
  forward = std::forward<T>(typename std::remove_reference_t<T>::type& t); // Issue

} // namespace libng