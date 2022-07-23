#pragma once

#include <libng_core/libng_common.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

// clang-format off

const f32 thePI      = 3.14159265358979323846f;
const f32 threehalfs = 1.5f;

#if LIBNG_OS_WINDOWS
#define LIBNG_FLT_EPSILON FLT_EPSILON
#else 
#define LIBNG_FLT_EPSILON 0.0f
#endif

// --------------------------------

template<class T> constexpr T    max(const T& a, const T& b)                  { return a > b ? a : b; }
template<class T> constexpr T    min(const T& a, const T& b)                  { return a < b ? a : b; }

template<class T> constexpr T    clamp   (const T& v, const T& a, const T& b) { return max(a, min(v, b)); }
template<class T> constexpr T    clamp01 (const T& v)                         { return clamp(v, 0, 1);    }
template<class T> constexpr T    saturate(const T& v)                         { return clamp01(v);        }

template<class T> constexpr T    byteToK(const T& v)                          { return v / 1024;                 }
template<class T> constexpr T    byteToM(const T& v)                          { return v / (1024 * 1024);        }
template<class T> constexpr T    byteToG(const T& v)                          { return v / (1024 * 1024 * 1024); }

template<class T> constexpr T    NaN()                                        { return std::numeric_limits<T>::quiet_NaN(); }
template<class T> constexpr bool isNaN(const T& rhs)                          { return std::isnan(rhs);                     }

template<class T> constexpr T    inf()                                        { return std::numeric_limits<T>::infinity();}
template<class T> constexpr bool isInf(const T& rhs)                          { return std::numeric_limits<T>::has_infinity; && rhs == inf<T>(); }

// --------------------------------

#if 0
#pragma mark -- Splits a floating-point value into fractional and integer parts --
#endif

LIBNG_INLINE float  modf(float  v, float*  i) { return std::modf(v, i); }
LIBNG_INLINE double modf(double v, double* i) { return std::modf(v, i); }

LIBNG_INLINE float  frac(float  v)            { float  intPart; return modf(v, &intPart); }
LIBNG_INLINE double frac(double v)            { double intPart; return modf(v, &intPart); }

LIBNG_INLINE float  ceil(float  a)            { return std::ceil(a); }
LIBNG_INLINE double ceil(double a)            { return std::ceil(a); }

LIBNG_INLINE float  floor(float  a)           { return std::floor(a); }
LIBNG_INLINE double floor(double a)           { return std::floor(a); }

// --------------------------------

#if 0
#pragma mark -- get remainder --
#endif
LIBNG_INLINE float  fmod(float  a, float  b)  { return std::fmod(a,b); }
LIBNG_INLINE double fmod(double a, double b)  { return std::fmod(a,b); }

#if LIBNG_COMPILER_VC | LIBNG_OS_CYGWIN
LIBNG_INLINE float  trunc(float  n)           { float  i; return std::modf(n, &i); }
LIBNG_INLINE double trunc(double n)           { double i; return std::modf(n, &i); }

LIBNG_INLINE float  round(float  a)           { return a > 0 ? floor(a + 0.5f) : ceil(a - 0.5f); }
LIBNG_INLINE double round(double a)           { return a > 0 ? floor(a + 0.5 ) : ceil(a - 0.5 ); }
#else
LIBNG_INLINE float  trunc(float  n)           { return std::trunc(n); }
LIBNG_INLINE double trunc(double n)           { return std::trunc(n); }

LIBNG_INLINE float  round(float  a)           { return std::round(a); }
LIBNG_INLINE double round(double a)           { return std::round(a); }
#endif

LIBNG_INLINE int    truncToInt(float  a)      { return static_cast<int>(trunc(a)); }
LIBNG_INLINE int    truncToInt(double a)      { return static_cast<int>(trunc(a)); }

LIBNG_INLINE int    roundToInt(float  a)      { return static_cast<int>(round(a)); }
LIBNG_INLINE int    roundToInt(double a)      { return static_cast<int>(round(a)); }

LIBNG_INLINE int    floorTo_Int(float  a)     { return static_cast<int>(floor(a)); }
LIBNG_INLINE int    floorTo_Int(double a)     { return static_cast<int>(floor(a)); }

LIBNG_INLINE int    ceilToInt(float  a)       { return static_cast<int>(ceil (a)); }
LIBNG_INLINE int    ceilToInt(double a)       { return static_cast<int>(ceil (a)); }

// --------------------------------

#if 0
#pragma mark -- Trigonometry --
#endif
  template<class T> constexpr    T      PI()            { return static_cast<T>(thePI); }
  template<class T> constexpr    T      twoPI()         { return PI<T>() * 2;           }
  template<class T> constexpr    T      halfPI()        { return PI<T>() * 0.5;         }

  template<class T> LIBNG_INLINE T      radians(T deg)  { return deg * (PI<T>() / static_cast<T>(180)); }
  template<class T> LIBNG_INLINE T      degrees(T rad)  { return rad * (static_cast<T>(180) / PI<T>()); }

                    LIBNG_INLINE float  sin(float  rad) { return ::sinf(rad); }
                    LIBNG_INLINE double sin(double rad) { return ::sin (rad); }

                    LIBNG_INLINE float  cos(float  rad) { return ::cosf(rad); }
                    LIBNG_INLINE double cos(double rad) { return ::cos (rad); }

                    LIBNG_INLINE float  tan(float  rad) { return ::tanf(rad); }
                    LIBNG_INLINE double tan(double rad) { return ::tan (rad); }

#if LIBNG_OS_MACOSX
  LIBNG_INLINE void sincos(float  rad, float & out_sin, float & out_cos) { ::__sincosf(rad, &out_sin, &out_cos); }
  LIBNG_INLINE void sincos(double rad, double& out_sin, double& out_cos) { ::__sincos (rad, &out_sin, &out_cos); }
#elif LIBNG_OS_LINUX
  LIBNG_INLINE void sincos(float  rad, float & out_sin, float & out_cos) { ::sincosf(rad, &out_sin, &out_cos); }
  LIBNG_INLINE void sincos(double rad, double& out_sin, double& out_cos) { ::sincos (rad, &out_sin, &out_cos); }
#else
  LIBNG_INLINE void sincos(float  rad, float & out_sin, float & out_cos) { out_sin = sin(rad); out_cos = cos(rad); }
  LIBNG_INLINE void sincos(double rad, double& out_sin, double& out_cos) { out_sin = sin(rad); out_cos = cos(rad); }
#endif

// --------------------------------

#if 0
#pragma mark -- common math -- 
#endif
template<class T> T abs(const T& v) { return v < 0 ? -v : v; }

template<class T> constexpr T    epsilon();
template<>        constexpr int  epsilon<int >() { return 0;            }
template<>        constexpr f32  epsilon<f32 >() { return FLT_EPSILON;  }
template<>        constexpr f64  epsilon<f64 >() { return DBL_EPSILON;  }
template<>        constexpr f128 epsilon<f128>() { return LDBL_EPSILON; }

template<class T, class EP = T> LIBNG_INLINE bool equals (const T& a, const T& b, const EP& ep = epsilon<T>()) { return abs(a - b) <= ep; }
template<class T, class EP = T> LIBNG_INLINE bool equals0(const T& a,             const EP& ep = epsilon<T>()) { return abs(a)     <= ep; }

// --------------------------------

#if 0
#pragma mark -- Lerp --
#pragma mark -- linear interpolation out = a + w * (b - a) --
#endif

template<class T, class W> LIBNG_INLINE T lerp(const T& a, const T& b, const W& w);

template<class T, class ENABLE = std::enable_if<std::is_floating_point_v<T>>> 
LIBNG_INLINE T lerp(T a, T b, T w) { 
  return (1 - w) * a + w * b; 
}

template<class T, class ENABLE = std::enable_if<std::is_integral_v<T>>>       
LIBNG_INLINE T lerp(T a, T b, double w) {
  double a_ = static_cast<double>(a);
  double b_ = static_cast<double>(b);
  return static_cast<T>(lerp<double>(a_, b_, w));
}

// --------------------------------
#if 0
#pragma mark -- sqrt --
#endif

LIBNG_INLINE float  sqrt(float  n) { return std::sqrt(n); }
LIBNG_INLINE double sqrt(double n) { return std::sqrt(n); }
LIBNG_INLINE int    sqrt(int    n) { return static_cast<int>(std::sqrt(static_cast<double>(n))); }

LIBNG_INLINE float  cbrt(float  n) { return std::cbrt(n); }
LIBNG_INLINE double cbrt(double n) { return std::cbrt(n); }
LIBNG_INLINE int    cbrt(int    n) { return static_cast<int>(std::cbrt(static_cast<double>(n))); }

// -- reciprocal square root --
LIBNG_INLINE float rsqrt_fast(float n) {
#if LIBNG_CPU_FEATURE_SSE2
  return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(n)));
#else // https://en.wikipedia.org/wiki/Fast_inverse_square_root
  f32 x2 = n * 0.5f;
  f32 y  = n;
  u32 i  = *reinterpret_cast<u32*>(&y);
      i  = 0x5F375A86UL - (i >> 1);
      y  = *reinterpret_cast<f32*>(&i);
      y  = y * (threehalfs - (x2 * y * y));
//    y  = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed
  return y;
#endif
}

LIBNG_INLINE double rsqrt_fast(double n) {
  f64 x2 = n * 0.5f;
  f64 y  = n;
  u64 i  = *reinterpret_cast<u64*>(&y);
      i  = 0x5FE6EB50C7B537A9ULL - (i >> 1);
      y  = *reinterpret_cast<f64*>(&i);
      y  = y * (threehalfs - (x2 * y * y));
//    y  = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed
  return y;
}

LIBNG_INLINE int rsqrt_fast(int n) {
  double d = static_cast<double>(n);
  return roundToInt(rsqrt_fast(d));
}

LIBNG_INLINE float rsqrt(float v) {
#if 0 // LIBNG_CPU_SSE2
  float  xrsqrt_est = rsqrt_fast(v);
  return xrsqrt_est * (1.5f - v * 0.5f * xrsqrt_est * xrsqrt_est); // NR iteration
#else
  return 1.0f / sqrt(v); 
#endif
}

LIBNG_INLINE double rsqrt(double v) { return 1.0 / sqrt(v); }
LIBNG_INLINE int    rsqrt(int    v) { return roundToInt(rsqrt(static_cast<double>(v))); }

// --------------------------------

#if 0
#pragma mark -- memory -- 
#endif
template<class T>
static constexpr T alignTo_uint(T n, T a) {
  static_assert(std::is_unsigned<T>::value, "");
  T r = n % a;
  return r ? (n + a - r) : n; // return (n + a - 1) / a * a;
}

constexpr size_t alignTo(size_t n, size_t a) {
  return alignTo_uint(n, a);
}

// --------------------------------

LIBNG_INLINE bool  isEq  (float a, float b, float epsilon = LIBNG_FLT_EPSILON) { return std::abs(a - b) < epsilon; }
LIBNG_INLINE bool  isPow2(int v)                                               { return !(v & (v - 1)) && v;       }

// --------------------------------

LIBNG_INLINE int32_t getNextPow2(int32_t v) {
  if (v <= 0) return 0;
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

} // namespace libng::math