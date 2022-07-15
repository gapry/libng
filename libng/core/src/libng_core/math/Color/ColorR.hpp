#pragma once

#include <libng_core/math/Color/ColorElementType.hpp>
#include <libng_core/math/Color/ColorModel.hpp>
#include <libng_core/math/Color/ColorType.hpp>

namespace libng::math {

template<class T>
struct ColorR {
  using ElementType                     = T;
  static const size_t kElementCount     = 1;
  static constexpr int kAlphaBits       = 0;
  static constexpr ColorType kColorType = libng::ColorType_make(ColorModel::R, ColorElementType_get<T>());

  union {
    struct {
      T r;
    };
    T data[kElementCount];
  };

  ColorR() = default;
  ColorR(const T& r_)
    : r(r_) {
  }
};

} // namespace libng::math
