#pragma once

#include <platform/os.hpp>
#include <ui/platform/win32/MSWindow.hpp>

#include <fmt/core.h>

namespace libng {

#if LIBNG_OS_WINDOWS
using UIWindowImpl = MSWindow;
#endif

class UIWindow : public UIWindowImpl {
public:
  UIWindow();

  ~UIWindow();
};

} // namespace libng