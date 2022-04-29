#pragma once

namespace libng {

template<class T>
struct Tuple3 {
  static const size_t kElement = 3;

  union {
    struct {
      T x, y, z;
    };
    T data[kElement];
  };

  Tuple3(const T& x_, const T& y_, const T& z_)
    : x(x_)
    , y(y_)
    , z(z_) {
  }
};

using Tuple3f = Tuple3<float>;
using Tuple3d = Tuple3<double>;

} // namespace libng