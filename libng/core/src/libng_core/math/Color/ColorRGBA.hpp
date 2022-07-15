#pragma once

#include <libng_core/math/Color/ColorRGB.hpp>
#include <libng_core/math/Tuple/Tuple4.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

template<class T>
struct ColorRGBA {
  using ElementType = T;

  static const size_t kElementCount     = 4;
  static constexpr int kAlphaBits       = sizeof(T) * 8;
  static constexpr ColorType kColorType = ColorType_make(ColorModel::RGBA, ColorElementType_get<T>());

  union {
    struct {
      T r, g, b, a;
    };
    T data[kElementCount];
  };

  ColorRGBA() = default;

  ColorRGBA(const T& r_, const T& g_, const T& b_, const T& a_)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_) {
  }

  ColorRGB<T> rgb() const {
    return ColorRGB(r, g, b);
  }

  Tuple4<T> toTuple() const {
    return Tuple4<T>(r, g, b, a);
  }

  operator Tuple4<T>() const {
    return toTuple();
  }

  void set(const T& r_, const T& g_, const T& b_, const T& a_) {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
  }

  template<class SE>
  void onJson(SE& se) {
    LIBNG_NAMED_IO(se, r);
    LIBNG_NAMED_IO(se, g);
    LIBNG_NAMED_IO(se, b);
    LIBNG_NAMED_IO(se, a);
  }
};

using ColorRGBAf = ColorRGBA<float>;
using ColorRGBAb = ColorRGBA<u8>;
using ColorRGBAs = ColorRGBA<u16>;

using Color4f = ColorRGBAf;
using Color4b = ColorRGBAb;

} // namespace libng::math
