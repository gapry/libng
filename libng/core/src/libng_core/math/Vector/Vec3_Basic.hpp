#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libng_common.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/maths.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/types/utility.hpp>

namespace libng::math {

// clang-format off

template<class T> using Vec3_Basic_Data = Tuple3<T>;
 
template<class T, class DATA = Vec3_Basic_Data<T>>
struct Vec3_Basic : public DATA {
public:
  static const size_t kElementCount = 3;
  
  using Vec3 = Vec3_Basic;
  using Vec2 = Vec2<T>;

  using ElementType = typename DATA::ElementType;

  using DATA::x; 
  using DATA::y;
  using DATA::z;

  using DATA::data;

  LIBNG_INLINE static Vec3 s_zero()    { return Vec3(0, 0, 0); }
  LIBNG_INLINE static Vec3 s_one()     { return Vec3(1, 1, 1); }

  LIBNG_INLINE static Vec3 s_forward() { return Vec3( 0,  0,  1); }
  LIBNG_INLINE static Vec3 s_back()    { return Vec3( 0,  0, -1); }
  LIBNG_INLINE static Vec3 s_up()      { return Vec3( 0,  1,  0); }
  LIBNG_INLINE static Vec3 s_down()    { return Vec3( 0, -1,  0); }
  LIBNG_INLINE static Vec3 s_right()   { return Vec3( 1,  0,  0); }
  LIBNG_INLINE static Vec3 s_left()    { return Vec3(-1,  0,  0); }

  LIBNG_INLINE static Vec3 s_inf()     { auto f = math::inf<T>(); return Vec3(f, f, f); }

  LIBNG_INLINE Vec3() = default;
  LIBNG_INLINE Vec3(const Tuple3<T> & v)                   { set(v); }
  LIBNG_INLINE Vec3(const T& x_, const T& y_, const T& z_) { set(x_,  y_,  z_); }
  LIBNG_INLINE Vec3(const Vec2& v, const T& z_)            { set(v.x, v.y, z_); }

  LIBNG_INLINE void set(const Tuple3<T> & v)                   { DATA::set(v); }
  LIBNG_INLINE void set(const T& x_, const T& y_, const T& z_) { set(Tuple3<T>(x_, y_, z_)); }

  LIBNG_INLINE bool equals (const Vec3& r, const T& epsilon = math::epsilon<T>()) const;
  LIBNG_INLINE bool equals0(               const T& epsilon = math::epsilon<T>()) const;

  LIBNG_INLINE void setAll(const T& v) { set(v,v,v); }
  LIBNG_INLINE bool isAll (const T& v) { return equals(Vec3(v,v,v)); }

  LIBNG_INLINE Vec3 operator+(const Vec3& r) const { return Vec3(x + r.x, y + r.y, z + r.z); }
  LIBNG_INLINE Vec3 operator-(const Vec3& r) const { return Vec3(x - r.x, y - r.y, z - r.z); }
  LIBNG_INLINE Vec3 operator*(const Vec3& r) const { return Vec3(x * r.x, y * r.y, z * r.z); }
  LIBNG_INLINE Vec3 operator/(const Vec3& r) const { return Vec3(x / r.x, y / r.y, z / r.z); }

  LIBNG_INLINE Vec3 operator+(const T& s) const { return Vec3(x + s, y + s, z + s); }
  LIBNG_INLINE Vec3 operator-(const T& s) const { return Vec3(x - s, y - s, z - s); }
  LIBNG_INLINE Vec3 operator*(const T& s) const { return Vec3(x * s, y * s, z * s); }
  LIBNG_INLINE Vec3 operator/(const T& s) const { return Vec3(x / s, y / s, z / s); }

  LIBNG_INLINE void operator+=(const Vec3& r) { x += r.x; y += r.y; z += r.z; }
  LIBNG_INLINE void operator-=(const Vec3& r) { x -= r.x; y -= r.y; z -= r.z; }
  LIBNG_INLINE void operator*=(const Vec3& r) { x *= r.x; y *= r.y; z *= r.z; }
  LIBNG_INLINE void operator/=(const Vec3& r) { x /= r.x; y /= r.y; z /= r.z; }

  LIBNG_INLINE void operator+=(const T& s) { x += s; y += s; z += s; }
  LIBNG_INLINE void operator-=(const T& s) { x -= s; y -= s; z -= s; }
  LIBNG_INLINE void operator*=(const T& s) { x *= s; y *= s; z *= s; }
  LIBNG_INLINE void operator/=(const T& s) { x /= s; y /= s; z /= s; }

  LIBNG_INLINE bool operator==(const Vec3& r) const { return x == r.x && y == r.y && z == r.z; }
  LIBNG_INLINE bool operator!=(const Vec3& r) const { return x != r.x || y != r.y || z != r.z; }

        T& operator[](int i)       { return data[i]; }
  const T& operator[](int i) const { return data[i]; }

  LIBNG_NODISCARD LIBNG_INLINE Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
  LIBNG_NODISCARD LIBNG_INLINE T    dot  (const Vec3& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

  LIBNG_NODISCARD LIBNG_INLINE T    magnitude   () const { return math::sqrt(sqrMagnitude()); }
  LIBNG_NODISCARD LIBNG_INLINE T    sqrMagnitude() const { return dot(*this); }

  LIBNG_NODISCARD LIBNG_INLINE T    length   () const { return magnitude();    }
  LIBNG_NODISCARD LIBNG_INLINE T    sqrLength() const { return sqrMagnitude(); }

  LIBNG_NODISCARD LIBNG_INLINE T    distance   (const Vec3 &r) const { return (*this - r).length();    }
  LIBNG_NODISCARD LIBNG_INLINE T    sqrDistance(const Vec3 &r) const { return (*this - r).sqrLength(); }

  LIBNG_NODISCARD Vec3 normalize() const { T m = magnitude(); return math::equals0(m) ? s_zero() : (*this / m); }

  LIBNG_INLINE  Vec2  xy() const { return Vec2(x,y); }
  LIBNG_INLINE  Vec2  xz() const { return Vec2(x,z); }

  Tuple3<T> toTuple() const { return Tuple3<T>(x,y,z); }
  operator Tuple3<T>() const { return toTuple(); }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {})", x, y, z);
  }
};

template<class T, class DATA> LIBNG_INLINE
bool Vec3_Basic<T, DATA>::equals(const Vec3& r, const T& epsilon) const {
  return math::equals(x, r.x, epsilon) && 
         math::equals(y, r.y, epsilon) && 
         math::equals(z, r.z, epsilon);
}

template<class T, class DATA> LIBNG_INLINE
bool Vec3_Basic<T, DATA>::equals0(const T& epsilon) const {
  return math::equals0(x, epsilon) && 
         math::equals0(y, epsilon) && 
         math::equals0(z, epsilon);
}

using Vec3f_Basic = Vec3_Basic<f32>;
using Vec3d_Basic = Vec3_Basic<f64>;

LIBNG_FORMATTER(math::Vec3f_Basic);
LIBNG_FORMATTER(math::Vec3d_Basic);

} // namespace libng::math