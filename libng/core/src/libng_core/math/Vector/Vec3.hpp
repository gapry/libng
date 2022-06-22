#pragma once

#include <cmath>
#include <iostream>

namespace libng {

template<typename T>
class Vec3 {
  static constexpr int kDimension = 3;

public:
  union {
    struct {
      T x, y, z;
    };
    T data[kDimension];
  };

  ~Vec3() = default;

  Vec3() = default;

  Vec3(T x_, T y_, T z_) {
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
};

template<typename T>
inline std::ostream& operator<<(std::ostream& s, const Vec3<T>& v) {
  s << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  return s;
}

using Vec3f = Vec3<float>;

} // namespace libng