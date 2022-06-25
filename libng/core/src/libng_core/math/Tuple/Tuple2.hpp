#pragma once

#include <libng_core/types/number.hpp>

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

  Tuple2() = default;

  Tuple2(const T& x_, const T& y_) {
    set(x_, y_);
  }

  void set(const Tuple2<T>& v) {
    *this = v;
  }

  void set(const T& x_, const T& y_) {
    x = x_;
    y = y_;
  }
};

using Tuple2f = Tuple2<f32>;
using Tuple2d = Tuple2<f64>;

} // namespace libng