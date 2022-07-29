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

  static void convert(math::Rect2f& o, const ::RECT& i) {
    o.x = static_cast<float>(i.left);
    o.y = static_cast<float>(i.top);
    o.w = static_cast<float>(i.right - i.left);
    o.h = static_cast<float>(i.bottom - i.top);
  }

  static void convert(math::Vec2f& o, const ::POINT& i) {
    o.x = static_cast<float>(i.x);
    o.y = static_cast<float>(i.y);
  }
};

} // namespace libng

#endif