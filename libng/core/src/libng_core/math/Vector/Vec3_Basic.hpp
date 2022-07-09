#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libng_common.hpp>
#include <libng_core/math/Maths.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

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
  static Vec3 s_inf()                               { auto inf = libng::math::inf<T>(); return Vec3(inf, inf, inf); }

  Vec3_Basic() = default;

  Vec3_Basic(const Tuple3<T>& rhs)                  { set(rhs);         }
  Vec3_Basic(const T& x_, const T& y_, const T& z_) { set(x_, y_, z_);  }

  void set(const Tuple3<T>& rhs)                    { DATA::set(rhs);             }
  void set(const T& x_, const T& y_, const T& z_)   { set(Tuple3<T>(x_, y_, z_)); }

  Vec3 operator+(const Vec3& rhs) const             { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
  Vec3 operator-(const Vec3& rhs) const             { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
  Vec3 operator*(const Vec3& rhs) const             { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
  Vec3 operator/(const Vec3& rhs) const             { return Vec3(x / rhs.x, y / rhs.y, z / rhs.z); }

  Vec3 operator+(T s) const                         { return Vec3(x + s, y + s, z + s); }
  Vec3 operator-(T s) const                         { return Vec3(x - s, y - s, z - s); }
  Vec3 operator*(T s) const                         { return Vec3(x * s, y * s, z * s); }
  Vec3 operator/(T s) const                         { return Vec3(x / s, y / s, z / s); }

  void operator+=(T s)                              { x += s; y += s; z += s; }
  void operator-=(T s)                              { x -= s; y -= s; z -= s; }
  void operator*=(T s)                              { x *= s; y *= s; z *= s; }
  void operator/=(T s)                              { x /= s; y /= s; z /= s; }
  // clang-format on

  Vec3 operator-() const {
    return Vec3(-x, -y, -z);
  }

  T magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  T length() const {
    return magnitude();
  }

  Vec3 normalize() const {
    T m = magnitude();
    if (!m)
      return Vec3(0, 0, 0);
    auto inv = 1 / m;
    return *this * inv;
  }

  T dot(const Vec3& r) const {
    return (x * r.x) + (y * r.y) + (z * r.z);
  }

  Vec3 cross(const Vec3& r) const {
    return Vec3(y * r.z - z * r.y,  //
                z * r.x - x * r.z,  //
                x * r.y - y * r.x); //
  }

  int size() const {
    return kDimension;
  }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "<{}, {}, {}>", x, y, z);
  }
};

using Vec3f_Basic = Vec3_Basic<f32>;
using Vec3d_Basic = Vec3_Basic<f64>;

LIBNG_FORMATTER(Vec3f_Basic);
LIBNG_FORMATTER(Vec3d_Basic);

} // namespace libng