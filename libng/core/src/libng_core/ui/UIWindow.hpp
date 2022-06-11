#pragma once

#include <fmt/core.h>
#include <libng_core/platform/os.hpp>
#include <libng_core/ui/platform/win32/MSWindow.hpp>

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