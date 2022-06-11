#pragma once

#include <libng_core/platform/os.hpp>
#include <libng_core/ui/platform/win32/MSApp.hpp>

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