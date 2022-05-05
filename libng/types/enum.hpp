#pragma once

// std
#include <type_traits>

// libng
#include <types/function.hpp>

template<class T>
LIBNG_INLINE constexpr typename std::underlying_type<T>::type enumToInt(T value) {
  return static_cast<typename std::underlying_type<T>::type>(value);
}

// clang-format off
#define LIBNG_ENUM_BITWISE_OPERATOR(T)                                                                         \
  LIBNG_INLINE T    operator~(T value)           { return static_cast<T>(~enumToInt(value));                 } \
  LIBNG_INLINE T    operator|(T one, T other)    { return static_cast<T>(enumToInt(one) | enumToInt(other)); } \
  LIBNG_INLINE T    operator&(T one, T other)    { return static_cast<T>(enumToInt(one) & enumToInt(other)); } \
  LIBNG_INLINE T    operator^(T one, T other)    { return static_cast<T>(enumToInt(one) ^ enumToInt(other)); } \
  LIBNG_INLINE void operator|=(T& one, T other)  { one = static_cast<T>(enumToInt(one) | enumToInt(other));  } \
  LIBNG_INLINE void operator&=(T& one, T other)  { one = static_cast<T>(enumToInt(one) & enumToInt(other));  } \
  LIBNG_INLINE void operator^=(T& one, T other)  { one = static_cast<T>(enumToInt(one) ^ enumToInt(other));  } \

#define LIBNG_ENUM_ARITHMETIC_OPERATOR(T)                                                  \
	constexpr T    operator+ (T  a, T b) { return static_cast<T>(enumInt(a) + enumInt(b)); } \
	constexpr T    operator- (T  a, T b) { return static_cast<T>(enumInt(a) - enumInt(b)); } \
	constexpr T    operator* (T  a, T b) { return static_cast<T>(enumInt(a) * enumInt(b)); } \
	constexpr T    operator/ (T  a, T b) { return static_cast<T>(enumInt(a) / enumInt(b)); } \
	constexpr void operator+=(T& a, T b) { a = static_cast<T>(enumInt(a) + enumInt(b)); }    \
	constexpr void operator-=(T& a, T b) { a = static_cast<T>(enumInt(a) - enumInt(b)); }    \
	constexpr void operator*=(T& a, T b) { a = static_cast<T>(enumInt(a) * enumInt(b)); }    \
	constexpr void operator/=(T& a, T b) { a = static_cast<T>(enumInt(a) / enumInt(b)); }    \

#define LIBNG_ENUM_ARITHMETIC_OPERATOR_INT(T)                                       \
	constexpr T    operator+ (T  a, int b) { return static_cast<T>(enumInt(a) + b); } \
	constexpr T    operator- (T  a, int b) { return static_cast<T>(enumInt(a) - b); } \
	constexpr T    operator* (T  a, int b) { return static_cast<T>(enumInt(a) * b); } \
	constexpr T    operator/ (T  a, int b) { return static_cast<T>(enumInt(a) / b); } \
	constexpr void operator+=(T& a, int b) { a = static_cast<T>(enumInt(a) + b); }    \
	constexpr void operator-=(T& a, int b) { a = static_cast<T>(enumInt(a) - b); }    \
	constexpr void operator*=(T& a, int b) { a = static_cast<T>(enumInt(a) * b); }    \
	constexpr void operator/=(T& a, int b) { a = static_cast<T>(enumInt(a) / b); }    \

  #define LIBNG_ENUM_ALL_OPERATOR(T)      \
	  LIBNG_ENUM_BITWISE_OPERATOR(T)        \
	  LIBNG_ENUM_ARITHMETIC_OPERATOR(T)     \
	  LIBNG_ENUM_ARITHMETIC_OPERATOR_INT(T) \