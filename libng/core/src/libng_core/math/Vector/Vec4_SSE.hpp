#pragma once

#include <libng_core/math/Vector/Vec4_Basic.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

template<class T, class M>
struct Vec4_SSE_Data {
  static const size_t kElementCount = 4;

  union {
    struct {
      T x, y, z, w;
    };
    T data[kElementCount];
    M _m;
  };
};

} // namespace libng::math