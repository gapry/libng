#pragma once

namespace libng::math {

template<class T>
struct ColorRGB {
  static const size_t kElement = 3;

  union {
    struct {
      T r, g, b;
    };
    T data[kElement];
  };

  ColorRGB(const T& r_, const T& g_, const T& b_)
    : r(r_)
    , g(g_)
    , b(b_) {
  }
};

} // namespace libng::math
