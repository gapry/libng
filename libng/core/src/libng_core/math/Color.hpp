#pragma once

#include <libng_core/types/number.hpp>

namespace libng {

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

template<class T>
struct ColorRGBA {
  static const size_t kElement = 4;

  union {
    struct {
      T r, g, b, a;
    };
    T data[kElement];
  };

  ColorRGBA(const T& r_, const T& g_, const T& b_, const T& a_)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_) {
  }

  ColorRGB<T> rgb() const {
    return ColorRGB(r, g, b);
  }
};

using ColorRGBAf = ColorRGBA<float>;
using ColorRGBAb = ColorRGBA<u8>;

using Color4f = ColorRGBAf;
using Color4b = ColorRGBAb;

} // namespace libng