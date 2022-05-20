
#pragma once

namespace libng {

template<class T>
class Vec2 {
  static const size_t kElement = 2;

public:
  union {
    struct {
      T x, y;
    };
    T data[kElement];
  };

  Vec2() = default;

  Vec2(const T& x_, const T& y_)
    : x(x_)
    , y(y_) {
  }

  ~Vec2() = default;

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

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

} // namespace libng