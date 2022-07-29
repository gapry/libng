#pragma once

#include <libng_core/math/Vector/Vec2_Basic.hpp>
#include <libng_core/platform/endian.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

// clang-format off

template<class T, class M>
struct Vec2_SSE_Data {
  static const size_t kElementCount = 2;

  using RegisterType = M;
  using ElementType  = T;

  union {
    struct { 
      T x;
      T y; 
    };
    T data[kElementCount];
    M _m;
  };

  LIBNG_INLINE Vec2_SSE_Data() = default;
  LIBNG_INLINE Vec2_SSE_Data(const T& x_, const T& y_) { static_assert(sizeof(Vec2_SSE_Data) == sizeof(T) * 2); set(x_, y_); }
  LIBNG_INLINE Vec2_SSE_Data(const Tuple2<T>& v)       { set(v.x, v.y); }

  LIBNG_INLINE void set(const Tuple2<T>& v)       { set(v.x, v.y);  }
  LIBNG_INLINE void set(const T& x_, const T& y_) { x = x_; y = y_; }

  LIBNG_INLINE        T& operator[](int i)       { return data[i]; }
  LIBNG_INLINE  const T& operator[](int i) const { return data[i]; }
};

using Vec2d_SSE_Data = Vec2_SSE_Data<double, __m128d>;

template<class T> struct Vec2_SSE_Select         { using Data = Vec2_Basic_Data<T>; };
template<>        struct Vec2_SSE_Select<double> { using Data = Vec2d_SSE_Data;     };

template<class T> 
using Vec2_SSE  = Vec2_Basic<T, typename Vec2_SSE_Select<T>::Data>;

using Vec2f_SSE = Vec2_SSE<float>;
using Vec2d_SSE = Vec2_SSE<double>;

LIBNG_INLINE Vec2d_SSE Vec2_SSE_make(__m128d m) { Vec2d_SSE o; o._m = m; return o; }

#if defined(LIBNG_ENDIAN_LITTLE)
template<> LIBNG_INLINE void Vec2d_SSE::set(const Tuple2<double>& v) { _m = _mm_set_pd(v.y, v.x); }
#elif defined(LIBNG_ENDIAN_BIG)
template<> LIBNG_INLINE void Vec2d_SSE::set(const Tuple2<double>& v) { _m = _mm_set_pd(v.x, v.y); }
#else
  #error
#endif

template<> LIBNG_INLINE Vec2d_SSE Vec2d_SSE::operator+(const Vec2& r) const { return Vec2_SSE_make(_mm_add_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec2d_SSE Vec2d_SSE::operator-(const Vec2& r) const { return Vec2_SSE_make(_mm_sub_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec2d_SSE Vec2d_SSE::operator*(const Vec2& r) const { return Vec2_SSE_make(_mm_mul_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec2d_SSE Vec2d_SSE::operator/(const Vec2& r) const { return Vec2_SSE_make(_mm_div_pd(_m, r._m)); }

} // namespace libng::math