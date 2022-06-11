#pragma once

#include <libng_core/math/Vector/Vec3.hpp>

namespace libng {

template<typename T>
class Vec4 {
  static constexpr int kDimension = 4;

public:
  union {
    struct {
      T x, y, z, w;
    };
    T data[kDimension];
  };

  ~Vec4() = default;

  Vec4() = default;

  Vec4(T x_, T y_, T z_, T w_) {
    set(x_, y_, z_, w_);
  }

  void set(T x_, T y_, T z_, T w_) {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
  }

  Vec3<T> toVec3() const {
    if (!w)
      return Vec3<T>(0, 0, 0);
    auto invW = 1 / w;
    return Vec3<T>(x, y, z) * invW;
  }

  // clang-format off
  Vec4 operator+(const Vec4& r) const { return Vec4(x + r.x, y + r.y, z + r.z, w + r.w); }
  Vec4 operator-(const Vec4& r) const { return Vec4(x - r.x, y - r.y, z - r.z, w - r.w); }
  Vec4 operator*(const Vec4& r) const { return Vec4(x * r.x, y * r.y, z * r.z, w * r.w); }
  Vec4 operator/(const Vec4& r) const { return Vec4(x / r.x, y / r.y, z / r.z, w / r.w); }

  Vec4 operator+(T s) const { return Vec4(x + s, y + s, z + s, w + s); }
  Vec4 operator-(T s) const { return Vec4(x - s, y - s, z - s, w - s); }
  Vec4 operator*(T s) const { return Vec4(x * s, y * s, z * s, w * s); }
  Vec4 operator/(T s) const { return Vec4(x / s, y / s, z / s, w / s); }

  void operator+=(T s) { x += s; y += s; z += s; w += s; }
  void operator-=(T s) { x -= s; y -= s; z -= s; w -= s; }
  void operator*=(T s) { x *= s; y *= s; z *= s; w *= s; }
	void operator/=(T s) { x /= s; y /= s; z /= s; w /= s; }
  // clang-format on

  int size() const {
    return kDimension;
  }
};

template<typename T>
inline std::ostream& operator<<(std::ostream& s, const Vec4<T>& v) {
  s << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
  return s;
}

using Vec4f = Vec4<float>;

} // namespace libng