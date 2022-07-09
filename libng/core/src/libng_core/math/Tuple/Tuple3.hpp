#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

template<class T>
struct Tuple3 {
  using ElementType = T; // Issue

  static const size_t kElement = 3;

  union {
    struct {
      T x, y, z;
    };
    T data[kElement];
  };

  // clang-format off
  Tuple3() = default;
  Tuple3(const T& x_, const T& y_, const T& z_)   { set(x_, y_, z_); }

  void set(const Tuple3<T>& rhs)                  { *this = rhs; }
  void set(const T& x_, const T& y_, const T& z_) { x = x_; y = y_; z = z_; }
  // clang-format on

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {})", x, y, z);
  }
};

using Tuple3f = Tuple3<f32>;
using Tuple3d = Tuple3<f64>;

LIBNG_FORMATTER(Tuple3f);
LIBNG_FORMATTER(Tuple3d);

} // namespace libng