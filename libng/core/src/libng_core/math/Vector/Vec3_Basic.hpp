#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libng_common.hpp>
#include <libng_core/math/Maths.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
using Vec3_Basic_Data = Tuple3<T>;

template<typename T, class DATA = Vec3_Basic_Data<T>>
struct Vec3_Basic : public DATA {
  static constexpr u8 kDimension = 3;

  using Vec3 = Vec3_Basic;
  using Vec2 = Vec2<T>;

  using DATA::x;
  using DATA::y;
  using DATA::z;

  using DATA::data;

  // clang-format off

  // Issue: LIBNG_INLINE u8 size() const                          { return kDimension; }
  LIBNG_INLINE static constexpr u8 size()                         { return kDimension; }

  LIBNG_INLINE static constexpr Vec3 s_inf()                      { auto inf = libng::math::inf<T>(); return Vec3(inf, inf, inf); }
  
  LIBNG_INLINE static constexpr Vec3 s_zero()                     { return Vec3( 0,  0,  0); }
  LIBNG_INLINE static constexpr Vec3 s_one()                      { return Vec3( 1,  1,  1); }
  
  LIBNG_INLINE static constexpr Vec3 s_forward()                  { return Vec3( 0,  0,  1); }
  LIBNG_INLINE static constexpr Vec3 s_back()                     { return Vec3( 0,  0, -1); }
  
  LIBNG_INLINE static constexpr Vec3 s_up()                       { return Vec3( 0,  1,  0); }
  LIBNG_INLINE static constexpr Vec3 s_down()                     { return Vec3( 0, -1,  0); }
  
  LIBNG_INLINE static constexpr Vec3 s_right()                    { return Vec3( 1,  0,  0); }
  LIBNG_INLINE static constexpr Vec3 s_left()                     { return Vec3(-1,  0,  0); }

  LIBNG_INLINE Vec3_Basic() = default;
  LIBNG_INLINE Vec3_Basic(const Tuple3<T>& rhs)                   { set(rhs);              }
  LIBNG_INLINE Vec3_Basic(const T x_, const T y_, const T z_)     { set(x_, y_, z_);       }
  LIBNG_INLINE Vec3_Basic(const Vec2& vec, const T& z_)           { set(vec.x, vec.y, z_); }

  LIBNG_INLINE void set(const Tuple3<T>& rhs)                     { DATA::set(rhs);             }
  LIBNG_INLINE void set(const T x_, const T y_, const T z_)       { set(Tuple3<T>(x_, y_, z_)); }

  LIBNG_INLINE Vec3 operator+(const Vec3& rhs) const              { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
  LIBNG_INLINE Vec3 operator-(const Vec3& rhs) const              { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
  LIBNG_INLINE Vec3 operator*(const Vec3& rhs) const              { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
  LIBNG_INLINE Vec3 operator/(const Vec3& rhs) const              { return Vec3(x / rhs.x, y / rhs.y, z / rhs.z); }

  LIBNG_INLINE Vec3 operator+(const T s) const                    { return Vec3(x + s, y + s, z + s); }
  LIBNG_INLINE Vec3 operator-(const T s) const                    { return Vec3(x - s, y - s, z - s); }
  LIBNG_INLINE Vec3 operator*(const T s) const                    { return Vec3(x * s, y * s, z * s); }
  LIBNG_INLINE Vec3 operator/(const T s) const                    { return Vec3(x / s, y / s, z / s); }

  LIBNG_INLINE void operator+=(const Vec3& rhs) const             { x += rhs.x; y += rhs.y; z += rhs.z; }
  LIBNG_INLINE void operator-=(const Vec3& rhs) const             { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
  LIBNG_INLINE void operator*=(const Vec3& rhs) const             { x *= rhs.x; y *= rhs.y; z *= rhs.z; }
  LIBNG_INLINE void operator/=(const Vec3& rhs) const             { x /= rhs.x; y /= rhs.y; z /= rhs.z; }

  LIBNG_INLINE void operator+=(const T s)                         { x += s; y += s; z += s; }
  LIBNG_INLINE void operator-=(const T s)                         { x -= s; y -= s; z -= s; }
  LIBNG_INLINE void operator*=(const T s)                         { x *= s; y *= s; z *= s; }
  LIBNG_INLINE void operator/=(const T s)                         { x /= s; y /= s; z /= s; }

  LIBNG_INLINE Vec3 operator-() const                             { return Vec3(-x, -y, -z); }

  LIBNG_INLINE T magnitude()                const                 { return std::sqrt(x * x + y * y + z * z); }
  LIBNG_INLINE T length   ()                const                 { return magnitude();                      }
  LIBNG_INLINE T distance (const Vec3& rhs) const                 { return (*this - rhs).magnitude();        }

  LIBNG_INLINE T    dot  (const Vec3& rhs) const                  { return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);                                    }
  LIBNG_INLINE Vec3 cross(const Vec3& rhs) const                  { return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,  x * rhs.y - y * rhs.x); }

  LIBNG_INLINE Vec3 normalize()            const                  { T m = magnitude(); return !m ? s_zero() : *this * (1 / m);                         }

  // clang-format on

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "<{}, {}, {}>", x, y, z);
  }
};

using Vec3f_Basic = Vec3_Basic<f32>;
using Vec3d_Basic = Vec3_Basic<f64>;

LIBNG_FORMATTER(math::Vec3f_Basic);
LIBNG_FORMATTER(math::Vec3d_Basic);

} // namespace libng::math