#pragma once

#include "platform/compiler.hpp"

#include <utility> // std::forward

template<class T>
GNET_INLINE constexpr auto enum_to_int(T value) -> typename std::underlying_type<T>::type {
  return static_cast<typename std::underlying_type<T>::type>(value);
}

// clang-format off
#define GNET_ENUM_BITWISE_OPERATOR(T)                                                                                    \
  GNET_INLINE auto operator~(T value)          -> T    { return static_cast<T>(~enum_to_int(value));                   } \
  GNET_INLINE auto operator|(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) | enum_to_int(other)); } \
  GNET_INLINE auto operator&(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) & enum_to_int(other)); } \
  GNET_INLINE auto operator^(T one, T other)   -> T    { return static_cast<T>(enum_to_int(one) ^ enum_to_int(other)); } \
  GNET_INLINE auto operator|=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) | enum_to_int(other));  } \
  GNET_INLINE auto operator&=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) & enum_to_int(other));  } \
  GNET_INLINE auto operator^=(T& one, T other) -> void { one = static_cast<T>(enum_to_int(one) ^ enum_to_int(other));  } \
// clang-format on

#define GNET_FORWARD(T) (std::forward<decltype(T)>(T))