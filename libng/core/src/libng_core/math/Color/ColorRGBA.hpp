#pragma once

#include <libng_core/math/Color/ColorRGB.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
struct ColorRGBA {
  static const size_t kElement = 4;

  union {
    struct {
      T r, g, b, a;
    };
    T data[kElement];
  };

  ColorRGBA(const T& r_, const T& g_, const T& b_, const T& a_)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_) {
  }

  ColorRGB<T> rgb() const {
    return ColorRGB(r, g, b);
  }
};

using ColorRGBAb = ColorRGBA<u8>;
using ColorRGBAf = ColorRGBA<f32>;

using Color4b = ColorRGBAb;
using Color4f = ColorRGBAf;

} // namespace libng::math
