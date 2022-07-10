#pragma once

#include <libng_core/libcxx/fmt.hpp>

namespace libng::math {

template<class T>
struct Tuple4 {
  static const size_t kElement = 4;

  union {
    struct {
      T x, y, z, w;
    };
    T data[kElement];
  };

  // clang-format off
	Tuple4() = default;
	Tuple4(const T& x_, const T& y_, const T& z_, const T& w_)   { set(x_, y_, z_, w_); }

	void set(const Tuple4<T>& v)                                 { *this = v; }
	void set(const T& x_, const T& y_, const T& z_, const T& w_) { x = x_; y = y_; z = z_; w = w_; }
  // clang-format o
  
  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {}, {})", x, y, z, w);
  }
};

using Tuple4f = Tuple4<float>;
using Tuple4d = Tuple4<double>;

LIBNG_FORMATTER(math::Tuple4f);
LIBNG_FORMATTER(math::Tuple4d);

} // namespace libng