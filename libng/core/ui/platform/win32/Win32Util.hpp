#pragma once

#include <platform/os.hpp>

#if LIBNG_OS_WINDOWS

#include <Windows.h>
#include <Windowsx.h>

#include <math/Rect2.hpp>

namespace libng {

struct Win32Util {
  Win32Util() = delete;

  static Rect2f toRect2f(const RECT& rc) {
    return Rect2f(static_cast<float>(rc.left),
                  static_cast<float>(rc.top),
                  static_cast<float>(rc.right - rc.left),
                  static_cast<float>(rc.bottom - rc.top));
  }
};

} // namespace libng

#endif