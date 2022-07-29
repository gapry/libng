#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/types/function.hpp>

namespace libng::math {

// clang-format off

template<class T> using Vec2_Basic_Data = Tuple2<T>;

template<class T, class DATA = Vec2_Basic_Data<T> >
struct Vec2_Basic : public DATA {
  static const size_t kElementCount = 2;

  using Vec2        = Vec2_Basic;
  using ElementType = T;

  using DATA::x;
  using DATA::y;

  LIBNG_INLINE Vec2() = default;
  LIBNG_INLINE Vec2(const Tuple2<T> & v)      { set(v);      }
  LIBNG_INLINE Vec2(const T& x_, const T& y_) { set(x_, y_); }

  LIBNG_INLINE void set(const Tuple2<T> & v)      { DATA::set(v);           }
  LIBNG_INLINE void set(const T& x_, const T& y_) { set(Tuple2<T>(x_, y_)); }

  LIBNG_INLINE bool equals (const Vec2& r, const T& epsilon = math::epsilon<T>()) const;
  LIBNG_INLINE bool equals0(               const T& epsilon = math::epsilon<T>()) const;

  LIBNG_INLINE void setAll(const T& v) { set(v,v); }
  LIBNG_INLINE bool isAll (const T& v) { return equals(Vec2(v,v)); }

  LIBNG_INLINE Vec2 operator+(const Vec2& r) const { return Vec2(x + r.x, y + r.y); }
  LIBNG_INLINE Vec2 operator-(const Vec2& r) const { return Vec2(x - r.x, y - r.y); }
  LIBNG_INLINE Vec2 operator*(const Vec2& r) const { return Vec2(x * r.x, y * r.y); }
  LIBNG_INLINE Vec2 operator/(const Vec2& r) const { return Vec2(x / r.x, y / r.y); }

  LIBNG_INLINE Vec2 operator+(const T& s) const { return Vec2(x + s, y + s); }
  LIBNG_INLINE Vec2 operator-(const T& s) const { return Vec2(x - s, y - s); }
  LIBNG_INLINE Vec2 operator*(const T& s) const { return Vec2(x * s, y * s); }
  LIBNG_INLINE Vec2 operator/(const T& s) const { return Vec2(x / s, y / s); }

  LIBNG_INLINE void operator+= (const Vec2& r) { x += r.x; y += r.y; }
  LIBNG_INLINE void operator-= (const Vec2& r) { x -= r.x; y -= r.y; }
  LIBNG_INLINE void operator*= (const Vec2& r) { x *= r.x; y *= r.y; }
  LIBNG_INLINE void operator/= (const Vec2& r) { x /= r.x; y /= r.y; }

  LIBNG_INLINE void operator+= (const T& s) { x += s; y += s; }
  LIBNG_INLINE void operator-= (const T& s) { x -= s; y -= s; }
  LIBNG_INLINE void operator*= (const T& s) { x *= s; y *= s; }
  LIBNG_INLINE void operator/= (const T& s) { x /= s; y /= s; }

  LIBNG_INLINE       T& operator[](int i)       { return data[i]; }
  LIBNG_INLINE const T& operator[](int i) const { return data[i]; }

  bool operator==(const Vec2& r) const { return x == r.x && y == r.y; }
  bool operator!=(const Vec2& r) const { return x != r.x || y != r.y; }

  Tuple2<T> toTuple()  const { return Tuple2<T>(x,y); }

  operator Tuple2<T>() const { return toTuple(); }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {})", x, y);
  }
};

template<class T, class DATA> LIBNG_INLINE
bool Vec2_Basic<T, DATA>::equals(const Vec2& r, const T& epsilon) const {
  return math::equals(x, r.x, epsilon) && 
         math::equals(y, r.y, epsilon);
}

template<class T, class DATA> LIBNG_INLINE
bool Vec2_Basic<T, DATA>::equals0(const T& epsilon) const {
  return math::equals0(x, epsilon) && 
         math::equals0(y, epsilon);
}

using Vec2i_Basic = Vec2_Basic<int>;
using Vec2f_Basic = Vec2_Basic<float>;
using Vec2d_Basic = Vec2_Basic<double>;

LIBNG_FORMATTER(math::Vec2i_Basic);
LIBNG_FORMATTER(math::Vec2f_Basic);
LIBNG_FORMATTER(math::Vec2d_Basic);

} // namespace libng::math