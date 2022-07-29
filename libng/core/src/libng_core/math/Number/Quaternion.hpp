#pragma once

#include <libng_core/math/Matrix/Mat4.hpp>

namespace libng::math {

// clang-format off

template<class T>
class Quat4 {
public:
  static const size_t kElementCount = 4;
  
  using ElementType = T;

  using Vec3 = libng::math::Vec3<T>;
  using Vec4 = libng::math::Vec4<T>;
  using Mat4 = libng::math::Mat4<T>;

  union {
    struct {
      T x, y, z, w;
    };
    T data[kElementCount];
  };

  explicit constexpr Quat4() = default;
  explicit constexpr Quat4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}

  constexpr void set(T x_, T y_, T z_, T w_) { x = x_; y = y_; z = z_; w = w_; }

  static Quat4 s_identity() { return Quat4(0, 0, 0, 1); }
  static Quat4 s_angleAxis(T rad, const Vec3& axis);

  static Quat4 s_euler(const Vec3& r);
  static Quat4 s_eulerX(T rad) { T s, c; math::sincos(rad * T(0.5), s, c); return Quat4(s, 0, 0, c); }
  static Quat4 s_eulerY(T rad) { T s, c; math::sincos(rad * T(0.5), s, c); return Quat4(0, s, 0, c); }
  static Quat4 s_eulerZ(T rad) { T s, c; math::sincos(rad * T(0.5), s, c); return Quat4(0, 0, s, c); }

  static Quat4 s_eulerDegX(T deg)  { return s_eulerX(math::radians(deg)); }
  static Quat4 s_eulerDegY(T deg)  { return s_eulerY(math::radians(deg)); }
  static Quat4 s_eulerDegZ(T deg)  { return s_eulerZ(math::radians(deg)); }

  T    angle() const { return math::acos(w) * T(2); }
  Vec3 axis () const;

  void setEuler (const Vec3& r)   { *this = s_euler(r);    }
  void setEulerX(      T     rad) { *this = s_eulerX(rad); }
  void setEulerY(      T     rad) { *this = s_eulerY(rad); }
  void setEulerZ(      T     rad) { *this = s_eulerZ(rad); }

  void setEulerDegX(T deg) { *this = s_eulerDegX(deg); }
  void setEulerDegY(T deg) { *this = s_eulerDegY(deg); }
  void setEulerDegZ(T deg) { *this = s_eulerDegZ(deg); }

  Vec3 euler()  const  { return Vec3(eulerX(), eulerY(), eulerZ()); }
     T eulerX() const;
     T eulerY() const;
     T eulerZ() const;

  Quat4 conjugate() const;
  Quat4 inverse()   const;

  T dot(const Quat4& r) const { return (x * r.x + y * r.y) + (z * r.z + w * r.w); }

  Quat4 operator*(const Quat4& r) const;
   Vec3 operator*(const  Vec3& v) const;

  Quat4 operator+(const Quat4& r) const { return Quat4(x + r.x, y + r.y, z + r.z, w + r.w); }
  Quat4 operator-(const Quat4& r) const { return Quat4(x - r.x, y - r.y, z - r.z, w - r.w); }

  Quat4 operator*(const     T& v) const { return Quat4(x * v, y * v, z * v, w * v); }
  Quat4 operator/(const     T& v) const { return Quat4(x / v, y / v, z / v, w / v); }

  Quat4 operator-()               const { return Quat4(-x, -y, -z, -w); }
};

template<class T, class W> LIBNG_INLINE
Quat4<T> lerp(const Quat4<T>& a, const Quat4<T>& b, const W& weight) {
  return Quat4<T>(lerp(a.x, b.x, weight),
                  lerp(a.y, b.y, weight),
                  lerp(a.z, b.z, weight),
                  lerp(a.w, b.w, weight));
}

template<class T, bool LONG_WAY = false> LIBNG_INLINE
Quat4<T> slerp(const Quat4<T>& a, const Quat4<T>& b, T weight) {
  Quat4<T> z = b;
  T cosTheta = a.dot(b);
#if 0 // LONG_WAY
  // If cosTheta < 0, the interpolation will take the long way around the sphere. 
  // To fix this, one quat must be negated.
  if (cosTheta < T(0)) {
    z        = -b;
    cosTheta = -cosTheta;
  }
#endif
  // Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
  if(cosTheta > T(1) - math::epsilon<T>()) {
    // Linear interpolation
    return math::lerp(a, z, weight);
  } else {
    // Essential Mathematics, page 467
    T angle = math::acos(cosTheta);
    return (a * math::sin((T(1) - weight) * angle) + z * math::sin(weight * angle)) / math::sin(angle);
  }
}

template<class T> LIBNG_INLINE
Quat4<T> slerp_longway(const Quat4<T> & a, const Quat4<T> & b, T weight) {
  return slerp<T, true>(a, b, weight);
}

template<class T> LIBNG_INLINE
Vec3<T> Quat4<T>::axis() const {
  T a = T(1) - w * w;
  if (a <= 0)
    return Vec3(0, 0, 1);
  T b = T(1) / math::sqrt(a);
  return Vec3(x, y, z) * b;
}

template<class T> LIBNG_INLINE
Quat4<T> Quat4<T>::s_euler(const Vec3& r) {
  Vec3 s, c;
  math::sincos(r * T(0.5), s, c);
  return Quat4(s.x * c.y * c.z - c.x * s.y * s.z,
               c.x * s.y * c.z + s.x * c.y * s.z,
               c.x * c.y * s.z - s.x * s.y * c.z,
               c.x * c.y * c.z + s.x * s.y * s.z);
}

template<class T> LIBNG_INLINE
T Quat4<T>::eulerZ() const {
  return math::atan2(T(2) * (x * y + w * z), w * w + x * x - y * y - z * z);
}

template<class T> LIBNG_INLINE
T Quat4<T>::eulerY() const {
  return math::asin(math::clamp(T(-2) * (x * z - w * y), T(-1), T(1)));
}

template<class T> LIBNG_INLINE
T Quat4<T>::eulerX() const {
  return math::atan2(T(2) * (y * z + w * x), w * w - x * x - y * y + z * z);
}

template<class T> LIBNG_INLINE
Quat4<T> Quat4<T>::conjugate() const {
  return Quat4(-x, -y, -z, w);
}

template<class T> LIBNG_INLINE
Quat4<T> Quat4<T>::inverse() const {
  T d = x * x + y * y + z * z + w * w;
  return Quat4(-x / d, -y / d, -z / d, w / d);
}

template<class T> LIBNG_INLINE
Vec3<T> Quat4<T>::operator*(const Vec3& v) const {
  Vec3 qv(x, y, z);
  auto uv  = qv.cross(v);
  auto uuv = qv.cross(uv);
  return v + (uv * w + uuv) * T(2);
}

template<class T> LIBNG_INLINE
Quat4<T> Quat4<T>::operator*(const Quat4& r) const {
  return Quat4(x * r.w + w * r.x + z * r.y - y * r.z,
               y * r.w + w * r.y + x * r.z - z * r.x,
               z * r.w + w * r.z + y * r.x - x * r.y,
               w * r.w - x * r.x - y * r.y - z * r.z);
}

template<class T> LIBNG_INLINE
Quat4<T> Quat4<T>::s_angleAxis(T rad, const Vec3& axis) {
  T s, c;
  math::sincos(rad * T(0.5), s, c);
  return Quat4(axis.x * s, axis.y * s, axis.z * s, c);
}

using Quat4f = Quat4<float>;
using Quat4d = Quat4<double>;

} // namespace libng::math