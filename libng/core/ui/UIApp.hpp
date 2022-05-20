#pragma once

#include <platform/os.hpp>
#include <ui/platform/win32/MSApp.hpp>

namespace libng {

#if LIBNG_OS_WINDOWS
using UIAppImpl = MSApp;
#endif

class UIApp : public UIAppImpl {
public:
  static UIApp* current();

  UIApp();

private:
  static UIApp* _current;
};

} // namespace libng