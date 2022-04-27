#pragma once

#include "platform/compiler.hpp"

#include <utility> // std::forward

template<class T>
LIBNG_INLINE constexpr auto enum_to_int(T value) -> typename std::underlying_type<T>::type {
  return static_cast<typename std::underlying_type<T>::type>(value);
}

// clang-format off
#define LIBNG_ENUM_BITWISE_OPERATOR(T)                                                                                    \
  LIBNG_INLINE auto operator~(T value)          -> T    { return static_cast<T>(~enum_to_int(value));                   } \
  LIBNG_INLINE auto operator|(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) | enum_to_int(other)); } \
  LIBNG_INLINE auto operator&(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) & enum_to_int(other)); } \
  LIBNG_INLINE auto operator^(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) ^ enum_to_int(other)); } \
  LIBNG_INLINE auto operator|=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) | enum_to_int(other));  } \
  LIBNG_INLINE auto operator&=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) & enum_to_int(other));  } \
  LIBNG_INLINE auto operator^=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) ^ enum_to_int(other));  } \
// clang-format on

#define LIBNG_FORWARD(T) (std::forward<decltype(T)>(T))