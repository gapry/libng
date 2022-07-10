#pragma once

namespace libng::math {

template<class T, class M>
struct Vec2_SSE_Data {
  static const size_t kElementCount = 2;

  union {
    struct {
      T x;
      T y;
    };
    T data[kElementCount];
    M m;
  };
};

} // namespace libng::math