#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/types/function.hpp>

namespace libng {

template<class T>
using Vec2_Basic_Data = Tuple2<T>;

template<class T, class DATA = Vec2_Basic_Data<T>>
struct Vec2_Basic : public DATA {
  static const size_t kElement = 2;

  using Vec2        = Vec2_Basic;
  using ElementType = T;

  using DATA::x;
  using DATA::y;

  // clang-format off
  LIBNG_INLINE          Vec2()                            { set(0, 0);   }
  LIBNG_INLINE          Vec2(const DATA& v)               { set(v); }
  LIBNG_INLINE          Vec2(const T& x_, const T& y_)    { set(x_, y_); }

  LIBNG_INLINE     void set(const DATA& v)                { DATA::set(v); }
  LIBNG_INLINE     void set(const T& x_, const T& y_)     { set(DATA(x_, y_)); }

  LIBNG_INLINE const T& operator[](int i)           const { LIBNG_ASSERT(i >= 0);      return data[i]; }
  LIBNG_INLINE       T& operator[](int i)                 { LIBNG_ASSERT(i >= 0);      return data[i]; }

  LIBNG_INLINE     Vec2 operator+(const Vec2& rhs)  const {                            return Vec2(x + rhs.x, y + rhs.y); }
  LIBNG_INLINE     Vec2 operator-(const Vec2& rhs)  const {                            return Vec2(x - rhs.x, y - rhs.y); }
  LIBNG_INLINE     Vec2 operator*(const Vec2& rhs)  const {                            return Vec2(x * rhs.x, y * rhs.y); }
  LIBNG_INLINE     Vec2 operator/(const Vec2& rhs)  const { LIBNG_ASSERT(rhs != 0);    return Vec2(x / rhs.x, y / rhs.y); }

  LIBNG_INLINE     Vec2 operator+(const T& scalar)  const {                            return Vec2(x + scalar, y + scalar); }
  LIBNG_INLINE     Vec2 operator-(const T& scalar)  const {                            return Vec2(x - scalar, y - scalar); }
  LIBNG_INLINE     Vec2 operator*(const T& scalar)  const {                            return Vec2(x * scalar, y * scalar); }
  LIBNG_INLINE     Vec2 operator/(const T& scalar)  const { LIBNG_ASSERT(scalar != 0); return Vec2(x / scalar, y / scalar); }

  LIBNG_INLINE     void operator+=(const Vec2& rhs)       {                            x += rhs.x; y += rhs.y; }
  LIBNG_INLINE     void operator-=(const Vec2& rhs)       {                            x -= rhs.x; y -= rhs.y; }
  LIBNG_INLINE     void operator*=(const Vec2& rhs)       {                            x *= rhs.x; y *= rhs.y; }
  LIBNG_INLINE     void operator/=(const Vec2& rhs)       { LIBNG_ASSERT(rhs != 0);    x /= rhs.x; y /= rhs.y; }

  LIBNG_INLINE     void operator+=(const T& scalar)       {                            x += scalar; y += scalar; }
  LIBNG_INLINE     void operator-=(const T& scalar)       {                            x -= scalar; y -= scalar; }
  LIBNG_INLINE     void operator*=(const T& scalar)       {                            x *= scalar; y *= scalar; }
  LIBNG_INLINE     void operator/=(const T& scalar)       { LIBNG_ASSERT(scalar != 0); x /= scalar; y /= scalar; }
  
  LIBNG_INLINE     bool operator==(const Vec2& rhs) const { return x == rhs.x  && y == rhs.y;  }
  LIBNG_INLINE     bool operator!=(const Vec2& rhs) const { return x != rhs.x  || y != rhs.y;  }
  LIBNG_INLINE     bool operator!=(const T& scalar) const { return x != scalar || y != scalar; }
  // clang-format on

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {})", x, y);
  }
};

using Vec2i_Basic = Vec2_Basic<i32>;
using Vec2f_Basic = Vec2_Basic<f32>;
using Vec2d_Basic = Vec2_Basic<f64>;

LIBNG_FORMATTER(Vec2i_Basic);
LIBNG_FORMATTER(Vec2f_Basic);
LIBNG_FORMATTER(Vec2d_Basic);

} // namespace libng