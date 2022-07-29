#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/math/Tuple/Tuple4.hpp>
#include <libng_core/math/Vector/Vec3.hpp>

namespace libng::math {

// clang-format off

template<class T> using Vec4_Basic_Data = Tuple4<T>;

template<class T, class DATA = Vec4_Basic_Data<T> >
struct Vec4_Basic : public DATA {
public: 
  static const size_t kElementCount = 4;

  using Vec4        = Vec4_Basic;
  using ElementType = typename DATA::ElementType;
  
  using DATA::x; 
  using DATA::y;
  using DATA::z;
  using DATA::w;
  using DATA::data;

  using Vec2 = Vec2<T>;
  using Vec3 = Vec3<T>;

  LIBNG_INLINE Vec4() = default;
  LIBNG_INLINE Vec4(const Tuple4<T> & v)                                { set(v);                 }
  LIBNG_INLINE Vec4(const T& x_, const T& y_, const T& z_, const T& w_) { set(x_, y_, z_, w_);    }
  LIBNG_INLINE Vec4(const Vec3& v, const T& w_)                         { set(v.x, v.y, v.z, w_); }

  LIBNG_INLINE void set(const Tuple4<T> & v)                                { DATA::set(v);                   }
  LIBNG_INLINE void set(const T& x_, const T& y_, const T& z_, const T& w_) { set(Tuple4<T>(x_, y_, z_, w_)); }

  LIBNG_INLINE bool equals (const Vec4& r, const T& epsilon = math::epsilon<T>()) const;
  LIBNG_INLINE bool equals0(               const T& epsilon = math::epsilon<T>()) const;

  LIBNG_INLINE void setAll(const T& v) { set(v,v,v,v); }
  LIBNG_INLINE bool isAll (const T& v) { return operator==(Vec4(v, v, v, v)); }

  LIBNG_INLINE Vec4 operator+(const Vec4& r) const { return Vec4(x + r.x, y + r.y, z + r.z, w + r.w); }
  LIBNG_INLINE Vec4 operator-(const Vec4& r) const { return Vec4(x - r.x, y - r.y, z - r.z, w - r.w); }
  LIBNG_INLINE Vec4 operator*(const Vec4& r) const { return Vec4(x * r.x, y * r.y, z * r.z, w * r.w); }
  LIBNG_INLINE Vec4 operator/(const Vec4& r) const { return Vec4(x / r.x, y / r.y, z / r.z, w / r.w); }

  LIBNG_INLINE Vec4 operator+(const T& s) const { return Vec4(x + s, y + s, z + s, w + s); }
  LIBNG_INLINE Vec4 operator-(const T& s) const { return Vec4(x - s, y - s, z - s, w - s); }
  LIBNG_INLINE Vec4 operator*(const T& s) const { return Vec4(x * s, y * s, z * s, w * s); }
  LIBNG_INLINE Vec4 operator/(const T& s) const { return Vec4(x / s, y / s, z / s, w / s); }

  LIBNG_INLINE void operator+=(const Vec4& r) { x += r.x; y += r.y; z += r.z; w += r.w; }
  LIBNG_INLINE void operator-=(const Vec4& r) { x -= r.x; y -= r.y; z -= r.z; w -= r.w; }
  LIBNG_INLINE void operator*=(const Vec4& r) { x *= r.x; y *= r.y; z *= r.z; w *= r.w; }
  LIBNG_INLINE void operator/=(const Vec4& r) { x /= r.x; y /= r.y; z /= r.z; w /= r.w; }

  LIBNG_INLINE void operator+=(const T& s) { x += s; y += s; z += s; w += s; }
  LIBNG_INLINE void operator-=(const T& s) { x -= s; y -= s; z -= s; w -= s; }
  LIBNG_INLINE void operator*=(const T& s) { x *= s; y *= s; z *= s; w *= s; }
  LIBNG_INLINE void operator/=(const T& s) { x /= s; y /= s; z /= s; w /= s; }

  LIBNG_INLINE bool operator==(const Vec4& r) const { return x == r.x && y == r.y && z == r.z && w == r.w; }
  LIBNG_INLINE bool operator!=(const Vec4& r) const { return x != r.x || y != r.y || z != r.z || w != r.w; }

        T& operator[](int i)       { return data[i]; }
  const T& operator[](int i) const { return data[i]; }

  Vec2 xy() const { return Vec2(x, y); }
  Vec2 xz() const { return Vec2(x, z); }
  Vec2 yz() const { return Vec2(y, z); }

  Vec3 xyz() const { return Vec3(x, y, z); }
  Vec3 xy0() const { return Vec3(x, y, 0); }
  Vec3 x0z() const { return Vec3(x, 0, z); }

  Vec3 toVec3() const { return (*this / w).xyz(); };

  Tuple4<T> toTuple() const { return Tuple4<T>(x, y, z, w); }

  operator Tuple4<T>() const { return toTuple(); }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {}, {})", x, y, z, w);
  }
};

template<class T, class DATA> LIBNG_INLINE
bool Vec4_Basic<T, DATA>::equals(const Vec4& r, const T& epsilon) const {
  return math::equals(x, r.x, epsilon) && 
         math::equals(y, r.y, epsilon) && 
         math::equals(z, r.z, epsilon) && 
         math::equals(w, r.w, epsilon);
}

template<class T, class DATA> LIBNG_INLINE
bool Vec4_Basic<T, DATA>::equals0(const T& epsilon) const {
  return math::equals0(x, epsilon) && 
         math::equals0(y, epsilon) && 
         math::equals0(z, epsilon) && 
         math::equals0(w, epsilon);
}

using Vec4f_Basic = Vec4_Basic<float>;
using Vec4d_Basic = Vec4_Basic<double>;

LIBNG_FORMATTER(math::Vec4f_Basic);
LIBNG_FORMATTER(math::Vec4d_Basic);

} // namespace libng::math