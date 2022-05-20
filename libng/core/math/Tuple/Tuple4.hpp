#pragma once

namespace libng {

template<class T>
struct Tuple4 {
  static const size_t kElement = 4;

  union {
    struct {
      T x, y, z, w;
    };
    T data[kElement];
  };

  Tuple4(const T& x_, const T& y_, const T& z_, const T& w_)
    : x(x_)
    , y(y_)
    , z(z_)
    , w(w_) {
  }
};

using Tuple4f = Tuple4<float>;
using Tuple4d = Tuple4<double>;

} // namespace libng