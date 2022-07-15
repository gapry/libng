#pragma once

namespace libng::math {

template<class T>
struct ColorR {
  static const size_t kElement = 1;

  union {
    struct {
      T r;
    };
    T data[kElement];
  };

  ColorR(const T& r_)
    : r(r_) {
  }
};

} // namespace libng::math
