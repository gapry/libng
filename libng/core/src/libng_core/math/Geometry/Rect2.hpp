#pragma once

#include <libng_core/math/Vector/Vec2.hpp>

namespace libng::math {

template<class T>
class Rect2 {
  static const size_t kElement = 4;

public:
  using Vec2 = Vec2<T>;

  union {
    struct {
      T x, y, w, h;
    };

    struct {
      Vec2 pos, size;
    };

    T data[kElement];
  };

  Rect2(const T& x_, const T& y_, const T& w_, const T& h_)
    : x(x_)
    , y(y_)
    , w(w_)
    , h(h_) {
  }

  Rect2(const Vec2& pos_, const Vec2& size_)
    : pos(pos_)
    , size(size_) {
  }

  ~Rect2() = default;
};

using Rect2i = Rect2<int>;
using Rect2f = Rect2<float>;
using Rect2d = Rect2<double>;

} // namespace libng::math