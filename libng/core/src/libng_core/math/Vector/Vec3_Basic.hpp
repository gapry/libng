#pragma once

#include <cmath>

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

template<class T>
using Vec3_Basic_Data = Tuple3<T>;

template<typename T, class DATA = Vec3_Basic_Data<T>>
struct Vec3_Basic : public DATA {
  static constexpr int kDimension = 3;

  using Vec3 = Vec3_Basic;
  using Vec2 = Vec2<T>;

  using DATA::x;
  using DATA::y;
  using DATA::z;

  using DATA::data;

  Vec3_Basic(T x_, T y_, T z_) {
    set(x_, y_, z_);
  }

  void set(T x_, T y_, T z_) {
    x = x_;
    y = y_;
    z = z_;
  }

  // clang-format off
  Vec3 operator+(const Vec3& r) const { return Vec3(x + r.x, y + r.y, z + r.z); }
  Vec3 operator-(const Vec3& r) const { return Vec3(x - r.x, y - r.y, z - r.z); }
  Vec3 operator*(const Vec3& r) const { return Vec3(x * r.x, y * r.y, z * r.z); }
  Vec3 operator/(const Vec3& r) const { return Vec3(x / r.x, y / r.y, z / r.z); }

  Vec3 operator+(T s) const { return Vec3(x + s, y + s, z + s); }
  Vec3 operator-(T s) const { return Vec3(x - s, y - s, z - s); }
  Vec3 operator*(T s) const { return Vec3(x * s, y * s, z * s); }
  Vec3 operator/(T s) const { return Vec3(x / s, y / s, z / s); }

  void operator+=(T s) { x += s; y += s; z += s; }
  void operator-=(T s) { x -= s; y -= s; z -= s; }
  void operator*=(T s) { x *= s; y *= s; z *= s; }
  void operator/=(T s) { x /= s; y /= s; z /= s; }
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
    fmt::format_to(ctx.out(), "({} {} {})", x, y, z);
  }
};

using Vec3f_Basic = Vec3_Basic<f32>;
using Vec3d_Basic = Vec3_Basic<f64>;

} // namespace libng