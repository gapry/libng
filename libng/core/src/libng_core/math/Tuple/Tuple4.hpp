#pragma once // clang-format off

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
struct Tuple4 {
  static const size_t kElement = 4;

  using ElementType = T;

  union {
    struct {
      T x, y, z, w;
    };
    T data[kElement];
  };

  LIBNG_INLINE Tuple4() = default;
  LIBNG_INLINE Tuple4(const T& x_, const T& y_, const T& z_, const T& w_)      { set(x_, y_, z_, w_); }

  LIBNG_INLINE void set   (const Tuple4<T>& v)                                 { *this = v; }
  LIBNG_INLINE void set   (const T& x_, const T& y_, const T& z_, const T& w_) { x = x_; y = y_; z = z_; w = w_; }
  LIBNG_INLINE void setAll(const T& v)                                         { set(v, v, v, v); }

  LIBNG_INLINE       T& operator[](int i)       { return data[i]; }
  LIBNG_INLINE const T& operator[](int i) const { return data[i]; }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {}, {})", x, y, z, w);
  }
};

using Tuple4i = Tuple4<i32>;
using Tuple4f = Tuple4<f32>;
using Tuple4d = Tuple4<f64>;

LIBNG_FORMATTER(math::Tuple4i);
LIBNG_FORMATTER(math::Tuple4f);
LIBNG_FORMATTER(math::Tuple4d);

} // namespace libng::math