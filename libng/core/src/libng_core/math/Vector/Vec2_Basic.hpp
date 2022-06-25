
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
  Vec2() = default;

  Vec2(const T& x_, const T& y_) {
    set(x_, y_);
  }

  void set(const DATA& v) {
    DATA::set(v);
  }

  void set(const T& x_, const T& y_) {
    set(DATA(x_, y_));
  }

  // clang-format off
	Vec2 operator+(const Vec2& r) const { return Vec2(x + r.x, y + r.y); }
	Vec2 operator-(const Vec2& r) const { return Vec2(x - r.x, y - r.y); }
	Vec2 operator*(const Vec2& r) const { return Vec2(x * r.x, y * r.y); }
	Vec2 operator/(const Vec2& r) const { return Vec2(x / r.x, y / r.y); }

	Vec2 operator+(const T& s) const { return Vec2(x + s, y + s); }
	Vec2 operator-(const T& s) const { return Vec2(x - s, y - s); }
	Vec2 operator*(const T& s) const { return Vec2(x * s, y * s); }
	Vec2 operator/(const T& s) const { return Vec2(x / s, y / s); }

	bool operator==(const Vec2& r) const { return x == r.x && y == r.y; }
	bool operator!=(const Vec2& r) const { return x != r.x || y != r.y; }
  // clang-format on
};

using Vec2i_Basic = Vec2_Basic<i32>;
using Vec2f_Basic = Vec2_Basic<f32>;
using Vec2d_Basic = Vec2_Basic<f64>;

} // namespace libng