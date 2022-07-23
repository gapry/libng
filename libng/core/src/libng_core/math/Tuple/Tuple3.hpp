#pragma once // clang-format off

#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
struct Tuple3 {
  using ElementType = T;

  static const size_t kElement = 3;

  union {
    struct {
      T x, y, z;
    };
    T data[kElement];
  };

  LIBNG_INLINE Tuple3() = default;
  LIBNG_INLINE Tuple3(const T& x_, const T& y_, const T& z_)      { set(x_, y_, z_); }

  LIBNG_INLINE void set   (const Tuple3<T>& v)                    { *this = v; }
  LIBNG_INLINE void set   (const T& x_, const T& y_, const T& z_) { x = x_; y = y_; z = z_; }
  LIBNG_INLINE void setAll(const T& v)                            { set(v, v, v); }

  LIBNG_INLINE       T& operator[](int i)                         { return data[i]; }
  LIBNG_INLINE const T& operator[](int i) const                   { return data[i]; }

  void onFormat(fmt::format_context& ctx) const {
    fmt::format_to(ctx.out(), "({}, {}, {})", x, y, z);
  }
};

using Tuple3i = Tuple3<i32>;
using Tuple3f = Tuple3<f32>;
using Tuple3d = Tuple3<f64>;

LIBNG_FORMATTER(math::Tuple3i);
LIBNG_FORMATTER(math::Tuple3f);
LIBNG_FORMATTER(math::Tuple3d);

} // namespace libng::math