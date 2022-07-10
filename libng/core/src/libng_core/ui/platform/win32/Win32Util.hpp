#pragma once

#include <libng_core/math/Geometry/Rect2.hpp>
#include <libng_core/platform/os.hpp>

#if LIBNG_OS_WINDOWS

namespace libng {

struct Win32Util {
  Win32Util() = delete;

  static math::Rect2f toRect2f(const RECT& rc) {
    return math::Rect2f(static_cast<float>(rc.left),
                        static_cast<float>(rc.top),
                        static_cast<float>(rc.right - rc.left),
                        static_cast<float>(rc.bottom - rc.top));
  }
};

} // namespace libng

#endif