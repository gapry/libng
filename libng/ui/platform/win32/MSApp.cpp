#include <ui/platform/win32/MSApp.hpp>

#if LIBNG_OS_WINDOWS

namespace libng {

MSApp::MSApp() {
}

MSApp::~MSApp() {
}

void MSApp::onCreate(CreateDesc& desc) {
  Base::onCreate(desc);
}

void MSApp::onRun() {
  Base::onRun();
  while (GetMessage(&_win32_msg, NULL, 0, 0)) {
    TranslateMessage(&_win32_msg);
    DispatchMessage(&_win32_msg);
  }
  willQuit();
}

void MSApp::onQuit() {
  Base::onQuit();
  ::PostQuitMessage(_exitCode);
}

} // namespace libng

#endif