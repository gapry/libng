#pragma once

#include <libng_core/math/Vector/Vec3_Basic.hpp>
#include <libng_core/platform/endian.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

// clang-format off

template<class T, class M>
struct Vec3_SSE_Data {
  static const size_t kElementCount = 3;

  using RegisterType = M;
  using ElementType  = T;

  union {
    struct { 
      T x, y, z, _unused_padding; 
    };
    T data[kElementCount];
    M _m;
  };

  LIBNG_INLINE Vec3_SSE_Data() = default;
  LIBNG_INLINE Vec3_SSE_Data(const T& x_, const T& y_, const T& z_) { static_assert(sizeof(Vec3_SSE_Data) == sizeof(T) * 4); set(x_, y_, z_); }
  LIBNG_INLINE Vec3_SSE_Data(const Tuple3<T>& v)                    { set(v.x, v.y, v.z); }

  LIBNG_INLINE void set(const Tuple3<T>& v)                    { set(v.x, v.y, v.z);     }
  LIBNG_INLINE void set(const T& x_, const T& y_, const T& z_) { x = x_; y = y_; z = z_; }

  LIBNG_INLINE       T& operator[](int i)       { return data[i]; }
  LIBNG_INLINE const T& operator[](int i) const { return data[i]; }
};

using Vec3f_SSE_Data = Vec3_SSE_Data<float,  __m128 >; // SSE
using Vec3d_SSE_Data = Vec3_SSE_Data<double, __m256d>; // AVX

template<class T> struct Vec3_SSE_Select         { using Data = Vec3_Basic_Data<T>; };
template<>        struct Vec3_SSE_Select<float > { using Data = Vec3f_SSE_Data; };
template<>        struct Vec3_SSE_Select<double> { using Data = Vec3d_SSE_Data; };

template<class T> 
using Vec3_SSE = Vec3_Basic<T, typename Vec3_SSE_Select<T>::Data >;

using Vec3f_SSE = Vec3_SSE<float>;
using Vec3d_SSE = Vec3_SSE<double>;

LIBNG_INLINE Vec3f_SSE Vec3_SSE_make(__m128  m) { Vec3f_SSE o; o._m = m; return o; }
LIBNG_INLINE Vec3d_SSE Vec3_SSE_make(__m256d m) { Vec3d_SSE o; o._m = m; return o; }

#if defined(LIBNG_ENDIAN_LITTLE)
template<> LIBNG_INLINE void Vec3f_SSE::set(const Tuple3<float >& v) { _m =    _mm_set_ps(0, v.z, v.y, v.x); }
template<> LIBNG_INLINE void Vec3d_SSE::set(const Tuple3<double>& v) { _m = _mm256_set_pd(0, v.z, v.y, v.x); }
#elif defined(LIBNG_ENDIAN_BIG)
template<> LIBNG_INLINE void Vec3f_SSE::set(const Tuple3<float >& v) { _m =    _mm_set_ps(v.x, v.y, v.z, 0); }
template<> LIBNG_INLINE void Vec3d_SSE::set(const Tuple3<double>& v) { _m = _mm256_set_pd(v.x, v.y, v.z, 0); }
#else
  #error
#endif

template<> LIBNG_INLINE Vec3f_SSE Vec3f_SSE::operator+(const Vec3& r) const { return Vec3_SSE_make(   _mm_add_ps(_m, r._m)); }
template<> LIBNG_INLINE Vec3f_SSE Vec3f_SSE::operator-(const Vec3& r) const { return Vec3_SSE_make(   _mm_sub_ps(_m, r._m)); }
template<> LIBNG_INLINE Vec3f_SSE Vec3f_SSE::operator*(const Vec3& r) const { return Vec3_SSE_make(   _mm_mul_ps(_m, r._m)); }
template<> LIBNG_INLINE Vec3f_SSE Vec3f_SSE::operator/(const Vec3& r) const { return Vec3_SSE_make(   _mm_div_ps(_m, r._m)); }

template<> LIBNG_INLINE Vec3d_SSE Vec3d_SSE::operator+(const Vec3& r) const { return Vec3_SSE_make(_mm256_add_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec3d_SSE Vec3d_SSE::operator-(const Vec3& r) const { return Vec3_SSE_make(_mm256_sub_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec3d_SSE Vec3d_SSE::operator*(const Vec3& r) const { return Vec3_SSE_make(_mm256_mul_pd(_m, r._m)); }
template<> LIBNG_INLINE Vec3d_SSE Vec3d_SSE::operator/(const Vec3& r) const { return Vec3_SSE_make(_mm256_div_pd(_m, r._m)); }

} // namespace libng::math