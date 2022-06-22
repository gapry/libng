#pragma once

#include <cfloat>
#include <cmath>
#include <cstdint>
#include <libng_core/types/function.hpp>

namespace libng {

const float thePI = 3.1415926535897f;

LIBNG_INLINE float getRad(float deg) {
  return deg / 360.f * 2 * 3.14159f;
}

LIBNG_INLINE bool isEq(float a, float b, float epsilon = FLT_EPSILON) {
  return std::abs(a - b) < epsilon;
}

LIBNG_INLINE int32_t getNextPow2(int32_t v) {
  if (v <= 0) {
    return 0;
  }

  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

LIBNG_INLINE bool isPow2(int v) {
  return !(v & (v - 1)) && v;
}

LIBNG_INLINE float getClamp(const float x, const float min, const float max) {
  if (x < min) {
    return min;
  } else if (x > max) {
    return max;
  } else {
    return x;
  }
}

LIBNG_INLINE void getSinAndCos(const float rad, float& outSin, float& outCos) {
  outSin = sin(rad);
  outCos = cos(rad);
}

LIBNG_INLINE float DegToRad(const float v) {
  return v * (thePI / 180.0f);
}

// clang-format off
namespace Math {
  template<class T> constexpr T max(const T& a, const T& b) { return a > b ? a : b; }
	template<class T> constexpr T min(const T& a, const T& b) { return a < b ? a : b; }

	template<class T> constexpr T byteToK(const T& v) { return v / 1024; }
	template<class T> constexpr T byteToM(const T& v) { return v / (1024 * 1024); }
	template<class T> constexpr T byteToG(const T& v) { return v / (1024 * 1024 * 1024); }
}

} // namespace libng