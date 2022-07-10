#pragma once

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/types/function.hpp>
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

  // clang-format off
  LIBNG_INLINE Tuple2() = default;
  LIBNG_INLINE Tuple2(const T& x_, const T& y_)   { set(x_, y_);    }

  LIBNG_INLINE void set(const Tuple2<T>& v)       { *this = v;      }
  LIBNG_INLINE void set(const T& x_, const T& y_) { x = x_; y = y_; }
  // clang-format on

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {})", x, y);
  }
};

using Tuple2i = Tuple2<i32>;
using Tuple2f = Tuple2<f32>;
using Tuple2d = Tuple2<f64>;

LIBNG_FORMATTER(math::Tuple2i);
LIBNG_FORMATTER(math::Tuple2f);
LIBNG_FORMATTER(math::Tuple2d);

} // namespace libng::math