#pragma once

namespace libng {

template<class T>
struct Tuple2 {
  static const size_t kElement = 2;

  union {
    struct {
      T x, y;
    };
    T data[kElement];
  };

  Tuple2(const T& x_, const T& y_)
    : x(x_)
    , y(y_) {
  }
};

using Tuple2f = Tuple2<float>;
using Tuple2d = Tuple2<double>;

} // namespace libng