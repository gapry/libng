#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/math/Tuple/Tuple4.hpp>
#include <libng_core/math/Vector/Vec3.hpp>

namespace libng::math {

template<class T>
using Vec4_Basic_Data = Tuple4<T>;

template<class T, class DATA = Vec4_Basic_Data<T>>
struct Vec4_Basic : public DATA {
public:
  static constexpr int kDimension = 4;

  using Vec4 = Vec4_Basic;

  using DATA::w;
  using DATA::x;
  using DATA::y;
  using DATA::z;

  using DATA::data;

  using Vec2 = Vec2<T>;
  using Vec3 = Vec3<T>;

  // clang-format off
	Vec4() = default;
	Vec4(const Tuple4<T> & v)                                { set(v); }
	Vec4(const T& x_, const T& y_, const T& z_, const T& w_) { set(x_, y_, z_, w_); }
	Vec4(const Vec3& v, const T& w_)                         { set(v.x, v.y, v.z, w_); }

	void set(const Tuple4<T> & v)                                { DATA::set(v); }
	void set(const T& x_, const T& y_, const T& z_, const T& w_) { set(Tuple4<T>(x_, y_, z_, w_)); }

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

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {}, {})", x, y, z, w);
  }
};

using Vec4f_Basic = Vec4_Basic<float>;
using Vec4d_Basic = Vec4_Basic<double>;

LIBNG_FORMATTER(math::Vec4f_Basic);
LIBNG_FORMATTER(math::Vec4d_Basic);

} // namespace libng::math