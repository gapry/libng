#include <libng_core/ui/platform/win32/MSApp.hpp>
#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/string.hpp>

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

String MSApp::onGetExecutableFilename() {
  wchar_t tmp[MAX_PATH + 1];
  if (!::GetModuleFileName(nullptr, tmp, MAX_PATH)) {
    throw LIBNG_ERROR("");
  }

  String o = UtfUtil::toString(tmp);
  return o;
}

String MSApp::onGetCurrentDir() {
  wchar_t tmp[MAX_PATH + 1];

  if (!::GetCurrentDirectory(MAX_PATH, tmp)) {
    throw LIBNG_ERROR("getCurrentDir");
  }

  String o = UtfUtil::toString(tmp);
  return o;
}

void MSApp::onSetCurrentDir(StrView dir) {
  TempStringW tmp = UtfUtil::toStringW(dir);
  ::SetCurrentDirectory(tmp.c_str());
}

} // namespace libng

#endif
