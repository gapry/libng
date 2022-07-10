#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
struct Tuple2 {
  static const size_t kElement = 2;

  union {
    struct {
      T x, y;
    };
    T data[kElement];
  };

  Tuple2() = default;

  Tuple2(const T& x_, const T& y_) {
    set(x_, y_);
  }

  // Tuple2(const Tuple2<T>& v) {
  //   set(v);
  // }

  // void operator=(const Tuple2<T>& rhs) {
  //   x = rhs.x;
  //   y = rhs.y;
  // }

  void set(const Tuple2<T>& v) {
    *this = v;
  }

  void set(const T& x_, const T& y_) {
    x = x_;
    y = y_;
  }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {})", x, y);
  }
};

using Tuple2f = Tuple2<f32>;
using Tuple2d = Tuple2<f64>;

LIBNG_FORMATTER(math::Tuple2f);
LIBNG_FORMATTER(math::Tuple2d);

} // namespace libng::math