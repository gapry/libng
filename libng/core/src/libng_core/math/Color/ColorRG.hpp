#pragma once

#include <libng_core/math/Color/ColorElementType.hpp>
#include <libng_core/math/Color/ColorModel.hpp>
#include <libng_core/math/Color/ColorType.hpp>

namespace libng::math {

template<class T>
struct ColorRG {
  using ElementType                     = T;
  static const size_t kElementCount     = 2;
  static constexpr int kAlphaBits       = 0;
  static constexpr ColorType kColorType = ColorType_make(ColorModel::RG, ColorElementType_get<T>());

  union {
    struct {
      T r, g;
    };
    T data[kElementCount];
  };

  ColorRG() = default;

  ColorRG(const T& r_, const T& g_)
    : r(r_)
    , g(g_) {
  }
};

} // namespace libng::math
