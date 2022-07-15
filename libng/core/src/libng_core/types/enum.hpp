#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/libng_common.hpp>
#include <libng_core/types/function.hpp>

// clang-format off

template<class T>
LIBNG_INLINE constexpr typename std::underlying_type<T>::type enumToInt(T value) {
  return static_cast<typename std::underlying_type<T>::type>(value);
}

#define LIBNG_ENUM_BITWISE_OPERATOR(T)                                                                         \
  LIBNG_INLINE T    operator~(T value)           { return static_cast<T>(~enumToInt(value));                 } \
  LIBNG_INLINE T    operator|(T one, T other)    { return static_cast<T>(enumToInt(one) | enumToInt(other)); } \
  LIBNG_INLINE T    operator&(T one, T other)    { return static_cast<T>(enumToInt(one) & enumToInt(other)); } \
  LIBNG_INLINE T    operator^(T one, T other)    { return static_cast<T>(enumToInt(one) ^ enumToInt(other)); } \
  LIBNG_INLINE void operator|=(T& one, T other)  { one = static_cast<T>(enumToInt(one) | enumToInt(other));  } \
  LIBNG_INLINE void operator&=(T& one, T other)  { one = static_cast<T>(enumToInt(one) & enumToInt(other));  } \
  LIBNG_INLINE void operator^=(T& one, T other)  { one = static_cast<T>(enumToInt(one) ^ enumToInt(other));  } \
  // ----

#define LIBNG_ENUM_ARITHMETIC_OPERATOR(T)                                                      \
  constexpr T    operator+ (T  a, T b) { return static_cast<T>(enumToInt(a) + enumToInt(b)); } \
  constexpr T    operator- (T  a, T b) { return static_cast<T>(enumToInt(a) - enumToInt(b)); } \
  constexpr T    operator* (T  a, T b) { return static_cast<T>(enumToInt(a) * enumToInt(b)); } \
  constexpr T    operator/ (T  a, T b) { return static_cast<T>(enumToInt(a) / enumToInt(b)); } \
  constexpr void operator+=(T& a, T b) { a = static_cast<T>(enumToInt(a) + enumToInt(b)); }    \
  constexpr void operator-=(T& a, T b) { a = static_cast<T>(enumToInt(a) - enumToInt(b)); }    \
  constexpr void operator*=(T& a, T b) { a = static_cast<T>(enumToInt(a) * enumToInt(b)); }    \
  constexpr void operator/=(T& a, T b) { a = static_cast<T>(enumToInt(a) / enumToInt(b)); }    \
  // ----

#define LIBNG_ENUM_ARITHMETIC_OPERATOR_INT(T)                                         \
  constexpr T    operator+ (T  a, int b) { return static_cast<T>(enumToInt(a) + b); } \
  constexpr T    operator- (T  a, int b) { return static_cast<T>(enumToInt(a) - b); } \
  constexpr T    operator* (T  a, int b) { return static_cast<T>(enumToInt(a) * b); } \
  constexpr T    operator/ (T  a, int b) { return static_cast<T>(enumToInt(a) / b); } \
  constexpr void operator+=(T& a, int b) { a = static_cast<T>(enumToInt(a) + b); }    \
  constexpr void operator-=(T& a, int b) { a = static_cast<T>(enumToInt(a) - b); }    \
  constexpr void operator*=(T& a, int b) { a = static_cast<T>(enumToInt(a) * b); }    \
  constexpr void operator/=(T& a, int b) { a = static_cast<T>(enumToInt(a) / b); }    \
  // ----

#define LIBNG_ENUM_ALL_OPERATOR(T)      \
  LIBNG_ENUM_BITWISE_OPERATOR(T)        \
  LIBNG_ENUM_ARITHMETIC_OPERATOR(T)     \
  LIBNG_ENUM_ARITHMETIC_OPERATOR_INT(T) \
  // ----

#define LIBNG_ENUM_STR__CASE(V) case E::V: return #V;

#define LIBNG_ENUM_STR(T)                                                \
  LIBNG_INLINE const char* enumStr(const T& v) {                         \
    using E = T;                                                         \
    switch (v) {                                                         \
      T##_ENUM_LIST(LIBNG_ENUM_STR__CASE) default : LIBNG_ASSERT(false); \
      return "";                                                         \
    }                                                                    \
  }                                                                      \
  // ----

#define LIBNG_ENUM_TRY_PARSE__CASE(V) \
  if (str == #V) {                    \
    outValue = E::V;                  \
    return true;                      \
  }                                   \
  // ----

#define LIBNG_ENUM_TRY_PARSE(T)                              \
  LIBNG_INLINE bool enumTryParse(T& outValue, StrView str) { \
    using E = T;                                             \
    T##_ENUM_LIST(LIBNG_ENUM_TRY_PARSE__CASE)                \
    return false;                                            \
  }                                                          \
  // ----

#define LIBNG_ENUM_STR_UTIL(T) \
  LIBNG_ENUM_STR(T)            \
  LIBNG_ENUM_TRY_PARSE(T)      \
  LIBNG_FORMATTER_ENUM(T)      \
  // ---

#define LIBNG_ENUM_DECLARE__ITEM(ITEM, VALUE) ITEM VALUE,

#define LIBNG_ENUM_DECLARE(T, BASE_TYPE)    \
  enum class T : BASE_TYPE {                \
    T##_ENUM_LIST(LIBNG_ENUM_DECLARE__ITEM) \
  };                                        \
  //----

#define LIBNG_ENUM_CLASS(T, BASE_TYPE) \
  LIBNG_ENUM_DECLARE(T, BASE_TYPE)     \
  LIBNG_ENUM_STR_UTIL(T)               \
  //----