#pragma once

namespace libng::math {

template<class T>
struct ColorRG {
  static const size_t kElement = 2;

  union {
    struct {
      T r, g;
    };
    T data[kElement];
  };

  ColorRG(const T& r_, const T& g_)
    : r(r_)
    , g(g_) {
  }
};

} // namespace libng::math
