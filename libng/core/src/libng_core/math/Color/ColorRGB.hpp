#pragma once

#include <libng_core/math/Color/ColorElementType.hpp>
#include <libng_core/math/Color/ColorModel.hpp>
#include <libng_core/math/Color/ColorType.hpp>

namespace libng::math {

template<class T>
struct ColorRGB {
  using ElementType                     = T;
  static const size_t kElementCount     = 3;
  static constexpr int kAlphaBits       = 0;
  static constexpr ColorType kColorType = libng::ColorType_make(ColorModel::RGB, ColorElementType_get<T>());

  union {
    struct {
      T r, g, b;
    };
    T data[kElementCount];
  };

  ColorRGB() = default;
  ColorRGB(const T& r_, const T& g_, const T& b_)
    : r(r_)
    , g(g_)
    , b(b_) {
  }
};

} // namespace libng::math
