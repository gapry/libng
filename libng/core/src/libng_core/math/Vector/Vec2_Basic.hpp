
#pragma once

#include <libng_core/math/Tuple/Tuple2.hpp>

namespace libng {

template<class T>
using Vec2_Basic_Data = Tuple2<T>;

template<class T, class DATA = Vec2_Basic_Data<T>>
class Vec2_Basic : public DATA {
  using Vec2                   = Vec2_Basic;
  static const size_t kElement = 2;

  using DATA::x;
  using DATA::y;

public:
  // clang-format off
  Vec2() = default;
  Vec2(const DATA& v)                    { set(v); }
  Vec2(const T& x_, const T& y_)         { set(x_, y_); }

  void set(const DATA& v)                { DATA::set(v); }
  void set(const T& x_, const T& y_)     { set(DATA(x_, y_)); }

	Vec2 operator+(const Vec2& rhs) const  { return Vec2(x + rhs.x, y + rhs.y); }
	Vec2 operator-(const Vec2& rhs) const  { return Vec2(x - rhs.x, y - rhs.y); }
	Vec2 operator*(const Vec2& rhs) const  { return Vec2(x * rhs.x, y * rhs.y); }
	Vec2 operator/(const Vec2& rhs) const  { return Vec2(x / rhs.x, y / rhs.y); }

	Vec2 operator+(const T& s)      const  { return Vec2(x + s, y + s); }
	Vec2 operator-(const T& s)      const  { return Vec2(x - s, y - s); }
	Vec2 operator*(const T& s)      const  { return Vec2(x * s, y * s); }
	Vec2 operator/(const T& s)      const  { return Vec2(x / s, y / s); }

	bool operator==(const Vec2& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Vec2& rhs) const { return x != rhs.x || y != rhs.y; }
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